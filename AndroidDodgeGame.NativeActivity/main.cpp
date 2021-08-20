/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include <malloc.h>
#include "util.h"
#include "graphics.h"
#include "meshutility.h"
#include "contextual.h"

struct engine 
{
	struct android_app* app;

	int infocus;
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	game_resources resources;

	struct game_state state;
};

static int engine_init_display(struct engine* engine) 
{
	const EGLint attribs[] = 
	{
		EGL_SURFACE_TYPE,
		EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_NONE
	};

	const EGLint contextattribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 3,
		EGL_NONE,
	};

	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;
	EGLSurface surface;
	EGLContext context;

	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

	eglInitialize(display, 0, 0);
	eglChooseConfig(display, attribs, &config, 1, &numConfigs);
	eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
	ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);
	surface = eglCreateWindowSurface(display, config, engine->app->window, NULL);
	context = eglCreateContext(display, config, NULL, contextattribs);

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) 
	{
		PK_LOGW("Unable to eglMakeCurrent");
		return -1;
	}

	eglQuerySurface(display, surface, EGL_WIDTH, &w);
	eglQuerySurface(display, surface, EGL_HEIGHT, &h);

	engine->display = display;
	engine->context = context;
	engine->surface = surface;
	engine->width = w;
	engine->height = h;
	engine->state.time = 0;
	engine->state.distance = 0;
	engine->state.ship_side = 1;
	engine->state.ship_pos_interpolant = 1;
	engine->state.speed = PK_MIN_SPEED;
	engine->state.speedMultiplier = 1.0f;

	initialize_resources(&engine->resources, engine->app->activity->assetManager);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return 0;
}

static void engine_render_frame(struct engine* engine) 
{
	if (engine->display == NULL)
	{
		return;
	}

	glClearColor(0, 0, 0, 1);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	graphics_context ctx = graphics_context();

	ctx.matrix_vp = matrix_viewprojection(95.0f, (float)engine->width / engine->height, 1.0f, PK_ROAD_LENGTH, { 0.0f, 5.0f, 0.0f }, { 40.0f, 0.0f, 0.0f });
	ctx.time = engine->state.time;
	ctx.distance = engine->state.distance;

	glDepthMask(GL_FALSE);
	draw_mesh(&ctx, &engine->resources.mesh_blitquad, &engine->resources.shader_background);
	glDepthMask(GL_TRUE);

	glDisable(GL_CULL_FACE);
	draw_mesh(&ctx, &engine->resources.mesh_road, &engine->resources.shader_road, PK_FLOAT4X4_IDENTITY);
	glEnable(GL_CULL_FACE);

	draw_obstacles(&ctx, &engine->resources, &engine->state);
	draw_ship(&ctx, &engine->resources, &engine->state);

	eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine) 
{
	if (engine->display != EGL_NO_DISPLAY) 
	{
		if (engine->context != EGL_NO_CONTEXT)
		{
			release_resources(&engine->resources);
		}

		eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (engine->context != EGL_NO_CONTEXT) 
		{
			eglDestroyContext(engine->display, engine->context);
		}

		if (engine->surface != EGL_NO_SURFACE) 
		{
			eglDestroySurface(engine->display, engine->surface);
		}

		eglTerminate(engine->display);
	}

	engine->infocus = 0;
	engine->display = EGL_NO_DISPLAY;
	engine->context = EGL_NO_CONTEXT;
	engine->surface = EGL_NO_SURFACE;
}

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) 
{
	if (AMotionEvent_getPointerCount(event) > 1)
	{
		return 0;
	}

	if ((uint)(AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK) == AMOTION_EVENT_ACTION_DOWN)
	{
		execute_game_command(&((struct engine*)app->userData)->state, PK_GAME_COMMAND_SWITCHSIDE);
		return 1;
	}

	return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) 
{
	struct engine* engine = (struct engine*)app->userData;

	switch (cmd) 
	{
		case APP_CMD_SAVE_STATE:
			engine->app->savedState = malloc(sizeof(struct game_state));
			*((struct game_state*)engine->app->savedState) = engine->state;
			engine->app->savedStateSize = sizeof(struct game_state);
			break;

		case APP_CMD_INIT_WINDOW:
			if (engine->app->window != NULL)
			{
				engine_init_display(engine);
				engine_render_frame(engine);
			}
			break;

		case APP_CMD_TERM_WINDOW:
			engine_term_display(engine);
			break;

		case APP_CMD_GAINED_FOCUS:
			engine->infocus = 1;
			break;

		case APP_CMD_LOST_FOCUS:
			engine->infocus = 0;
			engine_render_frame(engine);
			break;
	}
}

void android_main(struct android_app* state)
{
	struct engine engine;

	memset(&engine, 0, sizeof(engine));
	state->userData = &engine;
	state->onAppCmd = engine_handle_cmd;
	state->onInputEvent = engine_handle_input;
	engine.app = state;

	if (state->savedState != NULL) 
	{
		engine.state = *(struct game_state*)state->savedState;
	}

	engine.infocus = 1;

	while (true) 
	{
		int ident;
		int events;
		struct android_poll_source* source;

		while ((ident = ALooper_pollAll(engine.infocus ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
		{
			if (source != NULL)
			{
				source->process(state, source);
			}
		
			if (state->destroyRequested != 0)
			{
				engine_term_display(&engine);
				return;
			}
		}

		if (engine.infocus) 
		{
			update_gamestate(&engine.state);
			engine_render_frame(&engine);
		}
	}
}
