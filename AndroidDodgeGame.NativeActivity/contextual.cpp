#include "contextual.h"
#include "meshutility.h"

uint get_roadhash(const uint index)
{
	uint hash = wanghash(index);

	bool rightcolor = hash & (1 << 2);
	bool leftcolor = hash & (1 << 3);

	if (rightcolor == leftcolor)
	{
		hash &= ~(1 << (hash & (1 << 4) ? 1 : 0));
	}

	return hash;
}

uint get_roadflag(const uint roadhash, const uint side)
{
	if ((roadhash & (1 << side)) == 0)
	{
		return PK_ROAD_FLAG_NONE;
	}

	if (roadhash & (1 << (2 + side)))
	{
		return PK_ROAD_FLAG_DECC;
	}

	return PK_ROAD_FLAG_ACC;
}

void initialize_resources(game_resources* resources, AAssetManager* assetManager)
{
	resources->mesh_blitquad = create_mesh_quad2d({ -1.0f, -1.0f }, { 1.0f, 1.0f });
	resources->mesh_ship = create_mesh_ship();
	resources->mesh_cross = create_mesh_cross(0.2f, 1.0f);
	resources->mesh_wedge = create_mesh_wedge(0.2f, 1.0f);
	resources->mesh_pyramid = create_mesh_pyramid(0.2f, 1.0f);
	resources->mesh_octahedron = create_mesh_octahedron(0.2f, 1.0f);
	resources->mesh_road = create_mesh_road(8.0f, 200.0f, 0.2f, 0.75f, 64u);
	resources->shader_background = create_shader(assetManager, "sh_vs_background.vert", "sh_vs_background.frag");
	resources->shader_road = create_shader(assetManager, "sh_vs_road.vert", "sh_vs_road.frag");
	resources->shader_obstacle = create_shader(assetManager, "sh_vs_obstacle.vert", "sh_vs_obstacle.frag");
	resources->shader_ship = create_shader(assetManager, "sh_vs_ship.vert", "sh_vs_ship.frag");
	resources->shader_trail = create_shader(assetManager, "sh_vs_trail.vert", "sh_vs_trail.frag");
}

void release_resources(game_resources* resources)
{
	release_mesh(&resources->mesh_blitquad);
	release_mesh(&resources->mesh_cross);
	release_mesh(&resources->mesh_wedge);
	release_mesh(&resources->mesh_pyramid);
	release_mesh(&resources->mesh_octahedron);
	release_mesh(&resources->mesh_road);

	release_shader(&resources->shader_background);
	release_shader(&resources->shader_obstacle);
	release_shader(&resources->shader_road);
	release_shader(&resources->shader_ship);
	release_shader(&resources->shader_trail);
}

void execute_game_command(game_state* state, uint command)
{
	switch (command)
	{
		case PK_GAME_COMMAND_ACCELERATE:
			state->speed += PK_SPEED_INCREASE;
			state->speedMultiplier = 1.0f + PK_MIN_SPEED / state->speed;
			state->ship_trail_size = 1.2f;
			state->ship_z_offset = 2.0f;
			break;

		case PK_GAME_COMMAND_DECCELERATE:
			state->speed = max(PK_MIN_SPEED, state->speed * PK_SPEED_DECREASE_MULT);
			state->speedMultiplier = 0.0f;
			state->ship_trail_width = 0.25f;
			state->ship_z_offset = -1.0f;
			break;

		case PK_GAME_COMMAND_SWITCHSIDE:
			state->ship_side *= -1;
			break;
	}
}

void update_gamestate(game_state* state)
{
	state->time += PK_DELTA_TIME;
	state->distance += state->speed * PK_DELTA_TIME * state->speedMultiplier;
	state->speedMultiplier = lerp(state->speedMultiplier, 1.0f, PK_DELTA_TIME);

	uint fixedstep = (uint)floor((state->distance + PK_DISTANCE_BIAS) / PK_STEP_LENGTH);

	if (state->fixedstep != fixedstep)
	{
		state->fixedstep = fixedstep;

		uint flag = get_roadflag(get_roadhash(fixedstep), state->ship_side < 0 ? PK_ROAD_SIDE_L : PK_ROAD_SIDE_R);

		switch (flag)
		{
			case PK_ROAD_FLAG_ACC: execute_game_command(state, PK_GAME_COMMAND_ACCELERATE); break;
			case PK_ROAD_FLAG_DECC: execute_game_command(state, PK_GAME_COMMAND_DECCELERATE); break;
		}
	}
}

void draw_obstacles(graphics_context* ctx, game_resources* resources, game_state* state)
{
	set_pass(ctx, &resources->shader_obstacle);

	const uint offset = floor(ctx->distance / PK_STEP_LENGTH);
	const uint stepcount = floor(PK_ROAD_LENGTH / PK_STEP_LENGTH);
	const float fractdist = ctx->distance - offset * PK_STEP_LENGTH;

	for (uint i = 0u; i < stepcount; ++i)
	{
		uint hash = get_roadhash(offset + i);
		float elementdist = i * PK_STEP_LENGTH - fractdist;

		for (uint j = 0; j < 2; ++j)
		{
			uint flag = get_roadflag(hash, j);

			if (flag == PK_ROAD_FLAG_NONE)
			{
				continue;
			}

			float lr = -1.75f + j * 3.5f;

			switch (flag)
			{
				case PK_ROAD_FLAG_DECC:
					set_float4(ctx, "pk_Color", { 1.0f, 0.0, 0.0, 0.125f });
					draw_mesh(ctx, &resources->mesh_wedge, matrix_trs({ lr, 0.1f, elementdist + 1.5f }, float3(90, 135, 0), float3(1.5f, 1.5f, 0.5f)));
					set_float4(ctx, "pk_Color", { 1.0f, 0.0, 0.0, 0.0f });
					draw_mesh(ctx, &resources->mesh_cross, matrix_trs({ lr, 0.1f, elementdist + 0.0f }, float3(90, 45, 0), float3(1.5f, 1.5f, 0.5f)));
					break;
				case PK_ROAD_FLAG_ACC:
					set_float4(ctx, "pk_Color", { 0.0f, 0.7f, 1.0f, 0.0f });
					draw_mesh(ctx, &resources->mesh_wedge, matrix_trs({ lr, 0.1f, elementdist + 3.0f }, float3(90, -45, 0), float3(1.5f, 1.5f, 0.5f)));
					set_float4(ctx, "pk_Color", { 0.0f, 0.7f, 1.0f, 0.125f });
					draw_mesh(ctx, &resources->mesh_wedge, matrix_trs({ lr, 0.1f, elementdist + 1.5f }, float3(90, -45, 0), float3(1.5f, 1.5f, 0.5f)));
					set_float4(ctx, "pk_Color", { 0.0f, 0.7f, 1.0f, 0.25f });
					draw_mesh(ctx, &resources->mesh_wedge, matrix_trs({ lr, 0.1f, elementdist + 0.0f }, float3(90, -45, 0), float3(1.5f, 1.5f, 0.5f)));
					break;
			}
		}
	}
}

void draw_ship(graphics_context* ctx, game_resources* resources, game_state* state)
{
	float xpos = state->ship_pos_interpolant * 1.75f;
	float ypos = sin(ctx->time * 2.0f) * 0.25f + 0.75f;
	float zpos = state->ship_z_offset + 4.5f;

	state->ship_trail_size = lerp(state->ship_trail_size, 0.45f, PK_DELTA_TIME);
	state->ship_trail_width = lerp(state->ship_trail_width, 1.0f, PK_DELTA_TIME);
	state->ship_z_offset = lerp(state->ship_z_offset, 0, PK_DELTA_TIME);
	state->ship_pos_interpolant = lerpoutquad(state->ship_pos_interpolant, state->ship_side, PK_DELTA_TIME * 9.0f);
	state->ship_rot_interpolant = lerp(state->ship_rot_interpolant, state->ship_pos_interpolant, PK_DELTA_TIME * 5.0f);

	float tilt = (state->ship_pos_interpolant - state->ship_rot_interpolant) * -45.0f;
	float trailsize = state->ship_trail_size;
	float trailwidth0 = state->ship_trail_width * sin(PK_FLOAT_DEG2RAD * 2 * (ctx->time * 90)) * 1.5f;
	float trailwidth1 = state->ship_trail_width * sin(PK_FLOAT_DEG2RAD * 2 * (ctx->time * 90 + 45)) * 1.5f;
	float trailwidth2 = state->ship_trail_width * sin(PK_FLOAT_DEG2RAD * 2 * (ctx->time * 90 + 90)) * 1.5f;
	float trailwidth4 = state->ship_trail_width * 3.0f;

	draw_mesh(ctx, &resources->mesh_ship, &resources->shader_ship, matrix_trs({ xpos, ypos, zpos }, { 0, 0, tilt }, float3(0.15f)));

	glClear(GL_DEPTH_BUFFER_BIT);
	set_pass(ctx,  &resources->shader_trail);
	draw_mesh(ctx, &resources->mesh_octahedron, matrix_trs({ xpos, ypos, zpos - 1.0f }, { 0,  0, ctx->time * 90 }, { trailsize, trailwidth0, trailsize }));
	draw_mesh(ctx, &resources->mesh_octahedron, matrix_trs({ xpos, ypos, zpos - 1.0f }, { 0,  0, ctx->time * 90 + 45 }, { trailsize, trailwidth1, trailsize }));
	draw_mesh(ctx, &resources->mesh_octahedron, matrix_trs({ xpos, ypos, zpos - 1.0f }, { 0,  0, ctx->time * 90 + 90 }, { trailsize, trailwidth2, trailsize }));
	draw_mesh(ctx, &resources->mesh_pyramid, matrix_trs({ xpos, ypos, zpos - 1.0f }, { -90, 0, ctx->time * 180 }, { trailsize, trailwidth4, trailsize }));
}
