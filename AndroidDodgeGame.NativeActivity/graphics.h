#pragma once
#include "pkmath.h"

typedef GLuint shader;

constexpr char* UNIFORM_NAME_MATRIX_VP = "pk_MATRIX_VP";
constexpr char* UNIFORM_NAME_MATRIX_M = "pk_MATRIX_M";
constexpr char* UNIFORM_NAME_TIME = "pk_Time";
constexpr char* UNIFORM_NAME_DISTANCE = "pk_Distance";

struct mesh
{
    GLuint vertexArrayId;
    GLuint vertexBufferId;
    GLuint indexBufferId;
    GLuint indexCount;
};

struct vertex_attribute
{
    GLenum type;
    GLboolean normalized;
};

struct shader_source
{
    GLenum type;
    const char* source;
};

struct graphics_context
{
    const mesh* active_mesh = nullptr;
    const shader* active_shader = nullptr;

    float4x4 matrix_vp = PK_FLOAT4X4_IDENTITY;
    float time = 0;
    float distance = 0;
};

GLuint create_shader(const shader_source* sources, uint32_t count);

GLuint create_shader(const char* sourceVertex, const char* sourceFragment);

GLuint create_shader(AAssetManager* assetManager, const char* pathVertex, const char* pathFragment);

mesh create_mesh(const void* vertices, const uint32_t  vc, const GLuint* indices, const uint32_t ic, const vertex_attribute* attributes, uint32_t ac);

void release_shader(shader* shader);

void release_mesh(mesh* mesh);


void set_float(graphics_context* context, const char* name, float value);

void set_float4(graphics_context* context, const char* name, const float4& value);

void set_float4x4(graphics_context* context, const char* name, const float4x4& value);


void set_pass(graphics_context* context, const shader* shader);

void draw_mesh(graphics_context* context, const mesh* mesh);

void draw_mesh(graphics_context* context, const mesh* mesh, const float4x4& matrix);

void draw_mesh(graphics_context* context, const mesh* mesh, const shader* shader);

void draw_mesh(graphics_context* context, const mesh* mesh, const shader* shader, const float4x4& matrix);