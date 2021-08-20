#pragma once
#include "graphics.h"
#include "pkmath.h"

const float PK_DELTA_TIME = 1.0f / 60.0f;
const float PK_ROAD_LENGTH = 200.0f;
const float PK_STEP_LENGTH = 25.0f;
const float PK_MIN_SPEED = 20.0f;
const float PK_SPEED_INCREASE = 1.0f;
const float PK_SPEED_DECREASE_MULT = 0.9f;
const float PK_DISTANCE_BIAS = 5.0f;

const uint PK_GAME_COMMAND_ACCELERATE = 0;
const uint PK_GAME_COMMAND_DECCELERATE = 1;
const uint PK_GAME_COMMAND_SWITCHSIDE = 2;

const uint PK_ROAD_FLAG_NONE = 0;
const uint PK_ROAD_FLAG_ACC = 1;
const uint PK_ROAD_FLAG_DECC = 2;
const uint PK_ROAD_SIDE_L = 0;
const uint PK_ROAD_SIDE_R = 1;

struct game_state
{
	float time;
	float speed;
	float speedMultiplier;
	float distance;
	uint fixedstep;

	float ship_trail_size;
	float ship_trail_width;
	float ship_z_offset;
	float ship_pos_interpolant;
	float ship_rot_interpolant;
	int ship_side;
};

struct game_resources
{
	mesh mesh_blitquad;
	mesh mesh_ship;
	mesh mesh_cross;
	mesh mesh_wedge;
	mesh mesh_pyramid;
	mesh mesh_octahedron;
	mesh mesh_road;
	shader shader_background;
	shader shader_road;
	shader shader_obstacle;
	shader shader_ship;
	shader shader_trail;
};


uint get_roadhash(const uint seed);

uint get_roadflag(const uint roadhash, const uint side);

void initialize_resources(game_resources* resources, AAssetManager* assetManager);

void release_resources(game_resources* resources);

void execute_game_command(game_state* state, uint command);

void update_gamestate(game_state* state);

void draw_obstacles(graphics_context* ctx, game_resources* resources, game_state* state);

void draw_ship(graphics_context* ctx, game_resources* resources, game_state* state);
