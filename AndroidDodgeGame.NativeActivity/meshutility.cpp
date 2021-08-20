#include "meshutility.h"
#include "util.h"

struct vertex_default
{
    float4 position;
    float4 normal;
    float2 texcoord;
};

struct vertex_truncated
{
    float3 position;
    float3 normal;
    float2 texcoord;
};

mesh create_mesh_ship()
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE } };

    GLuint indices[] = 
    { 
        0, 1, 2, 0, 2, 3, 4, 5, 3, 4, 3, 6, 7, 8, 9, 7, 9, 10, 11, 12, 13, 11, 13, 14, 15, 16, 17, 15, 17, 18, 19, 20, 21, 19, 21, 22, 23, 24, 25, 
        26, 27, 28, 26, 28, 29, 30, 31, 32, 33, 34, 35, 35, 36, 33, 35, 37, 36, 33, 38, 34, 36, 39, 33, 40, 38, 41, 41, 42, 40, 38, 43, 41, 44, 45,
        43, 46, 47, 48, 46, 48, 49, 50, 51, 52, 50, 52, 53, 54, 55, 56, 54, 56, 57, 58, 59, 60, 60, 61, 58, 60, 62, 61, 63, 64, 65, 65, 66, 63, 65, 
        67, 66, 68, 69, 70, 68, 70, 71, 72, 73, 74, 72, 74, 75, 76, 77, 78, 76, 78, 79, 80, 81, 82, 82, 83, 80, 82, 84, 83, 85, 86, 87, 87, 88, 85, 
        88, 89, 85, 90, 91, 89, 92, 93, 94, 92, 94, 95, 96, 97, 98, 96, 98, 99, 100, 101, 102, 100, 102, 103, 104, 105, 106, 105, 107, 108, 105, 108, 
        109, 107, 110, 111, 107, 111, 112, 113, 114, 115, 116, 113, 117, 116, 117, 118, 119, 116, 120, 119, 120, 121, 121, 122, 123, 121, 123, 124, 125, 
        126, 127, 125, 127, 128, 129, 130, 131, 129, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 140, 139, 142, 143, 140, 143, 144, 140, 
        140, 144, 145, 140, 145, 141, 
    };

    float vertices[] =
    {
        0.6227598, 0, 0, 3, 0, 0, 1.5, 0, 16, 4.559755E-06, 0, 16, -3, 0, 0, -0.6227599, 0, 0, -1.5, 0, 16, -1.5, 0, 16, 1.5,
        0, 16, 0.5, 1, 16.75, -0.5, 1, 16.75, -3, 0, 0, -1.5, 0, 16, -0.5, 1, 16.75, -0.5, 2.5, 1.25, 1.5, 0, 16, 3, 0, 0, 0.5,
        2.5, 1.25, 0.5, 1, 16.75, -0.5, 1, 16.75, 0.5, 1, 16.75, 0.5, 2.5, 1.25, -0.5, 2.5, 1.25, 0.6380818, 0, -0.3936529, 3, 0, 
        0, 0.6227598, 0, 0, -3, 0, -0.5555554, -0.6426843, 0, -0.5119014, -0.6227599, 0, 0, -3, 0, 0, -3, 0, -4.5, -0.7979111, 0, -4.5,
        -0.7855983, 0, -4.183657, 0.7925679, 0.2287942, -4.362723, 0.7687193, 1.25, -3.75, 1.75, 1.25, -3.75, 1.32985, 0, -4.5, 3, 0, -4.5,
        -1.605554, 1.25, -3.75, 0.797911, 0, -4.5, -1.75, 1.25, -3.75, -0.7979111, 0, -4.5, -3, 0, -4.5, -0.7769594, 0.8971555, -3.961707, 
        1.495468E-07, 0.5662981, -4.160221, -0.7925679, 0.2287942, -4.362723, -3, 0, -4.5, -3, 0, 0, -0.5, 2.5, 1.25, -1.75, 1.25, -3.75, 3, 
        0, 0, 3, 0, -4.5, 1.75, 1.25, -3.75, 0.5, 2.5, 1.25, 1.75, 1.25, -3.75, -1.75, 1.25, -3.75, -0.5, 2.5, 1.25, 0.5, 2.5, 1.25, -4.5, -2.25,
        -6, -5.5, -2, -6, -3, 0, -4.5, -0.8083994, -0.4041997, -4.769466, -0.7979111, 0, -4.5, -5.5, -2, -2.75, -4.5, -2.25, -3, -0.6564152,
        -0.3282076, -0.8646751, -3, 0, 0, -0.6380818, 0, -0.393653, -4.5, -2.25, -3, -4.5, -2.25, -6, -0.8083994, -0.4041997, -4.769466, -0.6564152,
        -0.3282076, -0.8646751, -5.5, -2, -6, -5.5, -2, -2.75, -3, 0, 0, -3, 0, -4.5, -4.5, -2.25, -6, -4.5, -2.25, -3, -5.5, -2, -2.75, -5.5, -2,
        -6, 0.8083993, -0.4041997, -4.769466, 0.797911, 0, -4.5, 3, 0, -4.5, 4.5, -2.25, -6, 5.5, -2, -6, 0.6564151, -0.3282076, -0.864675, 4.5,
        -2.25, -3, 5.5, -2, -2.75, 3, 0, 0, 0.6401088, 0, -0.3933152, 0.6380818, 0, -0.3936529, 0.6507133, -0.2143526, -0.7181803, 4.5, -2.25, -6, 4.5,
        -2.25, -3, 0.6564151, -0.3282076, -0.864675, 0.8083993, -0.4041997, -4.769466, 5.5, -2, -2.75, 5.5, -2, -6, 3, 0, -4.5, 3, 0, 0, 4.5, -2.25, -3,
        4.5, -2.25, -6, 5.5, -2, -6, 5.5, -2, -2.75, 4.559755E-06, 0, 16, 0.6593458, -0.3806731, -0.9399702, 0.6380818, 0, -0.3936529, 0.8088164, -0.4669705,
        -4.780182, 0.8073381, -0.4036691, -4.742201, 0.6564151, -0.3282076, -0.864675, 0.8660254, -0.5000002, -6.25, 0.8660254, 0.2499993, -6.25, 0.7925679, 
        0.2287942, -4.362723, -0.6585919, -0.3802377, -0.9205994, 4.559755E-06, 0, 16, -0.6426843, 0, -0.5119014, -0.7958753, -0.4594986, -4.447696, -0.6564152,
        -0.3282076, -0.8646751, -0.7944828, -0.3972414, -4.411921, -0.8660254, -0.5, -6.25, -0.7855983, 0, -4.183657, -0.8660254, 9.933604E-09, -6.25,
        -0.7979111, 0, -4.5, -0.7925679, 0.2287942, -4.362723, -0.8660254, 0.2499993, -6.25, 0.7925679, 0.2287942, -4.362723, 0.8660254, 0.2499993, 
        -6.25, 0, 0.6249995, -6.25, 1.495468E-07, 0.5662981, -4.160221, -0.8660254, 0.2499993, -6.25, -0.7925679, 0.2287942, -4.362723, 1.495468E-07, 0.5662981,
        -4.160221, 0, 0.6249995, -6.25, 4.559755E-06, 0, 16, -8.940697E-08, -0.8750012, -6.25, 0.8660254, -0.5000002, -6.25, -8.940697E-08, -0.8750012, 
        -6.25, 4.559755E-06, 0, 16, -0.8660254, -0.5, -6.25, 0.8660254, 0.2499993, -6.25, 0, -0.1250003, -6.25, 0, 0.6249995, -6.25, 0.8660254, -0.5000002,
        -6.25, -8.940697E-08, -0.8750012, -6.25, -0.8660254, -0.5, -6.25, -0.8660254, 0.2499993, -6.25
    };

    return create_mesh(vertices, 146, indices, 240, attributes, 1);
}

mesh create_mesh_pyramid(float width, float height)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE } };

    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    const float3 vertices[] =
    {
        { -width, 0, -width },
        { -width, 0,  width },
        {  width, 0,  width },
        {  width, 0, -width },
        { 0, height, 0}
    };
    
    return create_mesh(vertices, 5, indices, 18, attributes, 1);
}

mesh create_mesh_octahedron(float width, float height)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE } };

    GLuint indices[] =
    {
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4,

        1, 0, 5,
        2, 1, 5,
        3, 2, 5,
        0, 3, 5
    };

    const float3 vertices[] =
    {
        { -width, 0, -width },
        { -width, 0,  width },
        {  width, 0,  width },
        {  width, 0, -width },
        { 0,  height, 0},
        { 0, -height, 0},
    };

    return create_mesh(vertices, 6, indices, 24, attributes, 1);
}

mesh create_mesh_wedge(float thickness, float size)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE }, { GL_FLOAT_VEC3, GL_TRUE }, { GL_FLOAT_VEC2, GL_FALSE } };
    
    const float t = thickness;
    const float s = size;

    GLuint* indices = PK_MEMORY_ALLOC(GLuint, 60);
    vertex_truncated* vertices = PK_MEMORY_ALLOC(vertex_truncated, 12);

    uint32_t j = 0u;

    vertices[j++] = { {-t, -s,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-t, -t,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-s, -t,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-s,  t,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { { t,  t,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { { t, -s,  t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };

    vertices[j++] = { {-t, -s, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-t, -t, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-s, -t, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { {-s,  t, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { { t,  t, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };
    vertices[j++] = { { t, -s, -t }, PK_FLOAT3_ZERO, PK_FLOAT2_ZERO };

    j = 0;

    // Front
    indices[j++] = 4;
    indices[j++] = 1;
    indices[j++] = 0;

    indices[j++] = 5;
    indices[j++] = 4;
    indices[j++] = 0;

    indices[j++] = 3;
    indices[j++] = 2;
    indices[j++] = 1;

    indices[j++] = 4;
    indices[j++] = 3;
    indices[j++] = 1;

    // Back
    indices[j++] = 6 + 0;
    indices[j++] = 6 + 1;
    indices[j++] = 6 + 4;

    indices[j++] = 6 + 0;
    indices[j++] = 6 + 4;
    indices[j++] = 6 + 5;

    indices[j++] = 6 + 1;
    indices[j++] = 6 + 2;
    indices[j++] = 6 + 3;

    indices[j++] = 6 + 1;
    indices[j++] = 6 + 3;
    indices[j++] = 6 + 4;

    for (int i = 0; i < 5; ++i)
    {
        indices[j++] = i + 0;
        indices[j++] = i + 1;
        indices[j++] = i + 7;

        indices[j++] = i + 0;
        indices[j++] = i + 7;
        indices[j++] = i + 6;
    }

    // Bottom
    indices[j++] = 5;
    indices[j++] = 0;
    indices[j++] = 6;

    indices[j++] = 5;
    indices[j++] = 6;
    indices[j++] = 11;

    mesh m = create_mesh(vertices, 12, indices, 60, attributes, 3);
    free(vertices);
    free(indices);
    return m;
}

mesh create_mesh_cross(float thickness, float size)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE }, { GL_FLOAT_VEC3, GL_TRUE }, { GL_FLOAT_VEC2, GL_FALSE } };

    const float t = thickness;
    const float s = size;
    const float u = t / s;

    float3 ld = { -1, -1, 0 };
    float3 lu = { -1, 1, 0 };
    float3 ru = { 1, 1, 0 };
    float3 rd = { 1, -1, 0 };

    ld = normalize(ld);
    lu = normalize(lu);
    ru = normalize(ru);
    rd = normalize(rd);

    GLuint* indices = PK_MEMORY_ALLOC(GLuint, 108);
    vertex_truncated* vertices = PK_MEMORY_ALLOC(vertex_truncated, 24);

    uint32_t j = 0u;

    vertices[j++] = { { -t, -s, t }, ld, {-u, -1 }};
    vertices[j++] = { { -t, -t, t }, ld, {-u, -u }};
    vertices[j++] = { { -s, -t, t }, ld, {-1, -u }};
    vertices[j++] = { { -s,  t, t }, lu, {-1,  u }};
    vertices[j++] = { { -t,  t, t }, lu, {-u,  u }};
    vertices[j++] = { { -t,  s, t }, lu, {-u,  1 }};
    vertices[j++] = { {  t,  s, t }, ru, { u,  1 }};
    vertices[j++] = { {  t,  t, t }, ru, { u,  u }};
    vertices[j++] = { {  s,  t, t }, ru, { 1,  u }};
    vertices[j++] = { {  s, -t, t }, rd, { 1, -u }};
    vertices[j++] = { {  t, -t, t }, rd, { u, -u }};
    vertices[j++] = { {  t, -s, t }, rd, { u, -1 }};

    vertices[j++] = {{ -t, -s, -t }, ld, {-u, -1 }};
    vertices[j++] = {{ -t, -t, -t }, ld, {-u, -u }};
    vertices[j++] = {{ -s, -t, -t }, ld, {-1, -u }};
    vertices[j++] = {{ -s,  t, -t }, lu, {-1,  u }};
    vertices[j++] = {{ -t,  t, -t }, lu, {-u,  u }};
    vertices[j++] = {{ -t,  s, -t }, lu, {-u,  1 }};
    vertices[j++] = {{  t,  s, -t }, ru, { u,  1 }};
    vertices[j++] = {{  t,  t, -t }, ru, { u,  u }};
    vertices[j++] = {{  s,  t, -t }, ru, { 1,  u }};
    vertices[j++] = {{  s, -t, -t }, rd, { 1, -u }};
    vertices[j++] = {{  t, -t, -t }, rd, { u, -u }};
    vertices[j++] = {{  t, -s, -t }, rd, { u, -1 }};

    j = 0;

    // Front
    indices[j++] = 10;
    indices[j++] = 1;
    indices[j++] = 0;
    
    indices[j++] = 11;
    indices[j++] = 10;
    indices[j++] = 0;

    indices[j++] = 8;
    indices[j++] = 3;
    indices[j++] = 2;

    indices[j++] = 9;
    indices[j++] = 8;
    indices[j++] = 2;

    indices[j++] = 6;
    indices[j++] = 5;
    indices[j++] = 4;

    indices[j++] = 7;
    indices[j++] = 6;
    indices[j++] = 4;

    // Back
    indices[j++] = 12 + 0;
    indices[j++] = 12 + 1;
    indices[j++] = 12 + 10;

    indices[j++] = 12 + 0;
    indices[j++] = 12 + 10;
    indices[j++] = 12 + 11;

    indices[j++] = 12 + 2;
    indices[j++] = 12 + 3;
    indices[j++] = 12 + 8;

    indices[j++] = 12 + 2;
    indices[j++] = 12 + 8;
    indices[j++] = 12 + 9;

    indices[j++] = 12 + 4;
    indices[j++] = 12 + 5;
    indices[j++] = 12 + 6;

    indices[j++] = 12 + 4;
    indices[j++] = 12 + 6;
    indices[j++] = 12 + 7;

    for (int i = 0; i < 11; ++i)
    {
        indices[j++] = i + 0;
        indices[j++] = i + 1;
        indices[j++] = i + 13;

        indices[j++] = i + 0;
        indices[j++] = i + 13;
        indices[j++] = i + 12;
    }

    // Bottom
    indices[j++] = 11;
    indices[j++] = 0;
    indices[j++] = 12;

    indices[j++] = 11;
    indices[j++] = 12;
    indices[j++] = 23;

    mesh m = create_mesh(vertices, 24, indices, 108, attributes, 3);
    free(vertices);
    free(indices);
    return m;
}

mesh create_mesh_road(float width, float length, float edgewidth, float elevation, uint32_t segments)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE }, { GL_FLOAT_VEC3, GL_TRUE }, { GL_FLOAT_VEC2, GL_FALSE } };

    const uint32_t vps = 6;
    const uint32_t tps = 6;
    const uint32_t indexcount = tps * (segments - 1) * 3;
    const uint32_t vertexcount = segments * vps;

    const float il = length / segments;
    const float wo = width * 0.5f;
    const float ew = wo * edgewidth;

    float3 normaledge0 = { +ew, elevation, 0 };
    float3 normaledge1 = { -ew, elevation, 0 };
    normaledge0 = normalize(normaledge0);
    normaledge1 = normalize(normaledge1);
    float3 normalup = PK_FLOAT3_UP;

    GLuint* indices = PK_MEMORY_ALLOC(GLuint, indexcount);
    vertex_truncated* vertices = PK_MEMORY_ALLOC(vertex_truncated, vertexcount);

    for (uint i = 0; i < segments; ++i)
    {
        int ic = i * tps * 3;
        int iv = i * vps;

        vertices[iv + 0] = { { -wo, elevation, il * i }, normaledge0, { (float)i, 0.0f } };
        vertices[iv + 1] = { { -wo + ew, 0.0f, il * i }, normaledge0, { (float)i, edgewidth } };
        vertices[iv + 2] = { { -wo + ew, 0.0f, il * i }, normalup, { (float)i, edgewidth } };
        vertices[iv + 3] = { { +wo - ew, 0.0f, il * i }, normalup, { (float)i, 1.0f - edgewidth } };
        vertices[iv + 4] = { { +wo - ew, 0.0f, il * i }, normaledge1, { (float)i, 1.0f - edgewidth } };
        vertices[iv + 5] = { { +wo, elevation, il * i }, normaledge1, { (float)i, 1.0f } };

        if (i >= segments - 1)
        {
            continue;
        }

        indices[ic + 0] = iv + vps + 0;
        indices[ic + 1] = iv + vps + 1;
        indices[ic + 2] = iv + 0;

        indices[ic + 3] = iv + vps + 1;
        indices[ic + 4] = iv + 1;
        indices[ic + 5] = iv + 0;


        indices[ic + 6] = iv + vps + 2;
        indices[ic + 7] = iv + vps + 3;
        indices[ic + 8] = iv + 2;

        indices[ic + 9] = iv + vps + 3;
        indices[ic + 10] = iv + 3;
        indices[ic + 11] = iv + 2;


        indices[ic + 12] = iv + vps + 4;
        indices[ic + 13] = iv + vps + 5;
        indices[ic + 14] = iv + 4;

        indices[ic + 15] = iv + vps + 5;
        indices[ic + 16] = iv + 5;
        indices[ic + 17] = iv + 4;
    }

    mesh m = create_mesh(vertices, vertexcount, indices, indexcount, attributes, 3);
    free(vertices);
    free(indices);
    return m;
}

mesh create_mesh_box(const float3& offset, const float3& extents)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC3, GL_FALSE }, { GL_FLOAT_VEC3, GL_TRUE }, { GL_FLOAT_VEC2, GL_FALSE } };

    float3 p0 = { offset.x - extents.x, offset.y - extents.y, offset.z + extents.z };
    float3 p1 = { offset.x + extents.x, offset.y - extents.y, offset.z + extents.z };
    float3 p2 = { offset.x + extents.x, offset.y - extents.y, offset.z - extents.z };
    float3 p3 = { offset.x - extents.x, offset.y - extents.y, offset.z - extents.z };
    float3 p4 = { offset.x - extents.x, offset.y + extents.y, offset.z + extents.z };
    float3 p5 = { offset.x + extents.x, offset.y + extents.y, offset.z + extents.z };
    float3 p6 = { offset.x + extents.x, offset.y + extents.y, offset.z - extents.z };
    float3 p7 = { offset.x - extents.x, offset.y + extents.y, offset.z - extents.z };

    float3 up = PK_FLOAT3_UP;
    float3 down = PK_FLOAT3_DOWN;
    float3 front = PK_FLOAT3_FORWARD;
    float3 back = PK_FLOAT3_BACKWARD;
    float3 left = PK_FLOAT3_LEFT;
    float3 right = PK_FLOAT3_RIGHT;

    float2 uv00 = { 0.0f, 0.0f };
    float2 uv10 = { 1.0f, 0.0f };
    float2 uv01 = { 0.0f, 1.0f };
    float2 uv11 = { 1.0f, 1.0f };

    vertex_truncated vertices[] =
    {
        // Bottom
        { p0, down, uv11 },
        { p1, down, uv01 },
        { p2, down, uv00 },
        { p3, down, uv10 },

        // Left
        { p7, left, uv11 },
        { p4, left, uv01 },
        { p0, left, uv00 },
        { p3, left, uv10 },

        // Front
        { p4, front, uv11 },
        { p5, front, uv01 },
        { p1, front, uv00 },
        { p0, front, uv10 },

        // Back
        { p6, back, uv11 },
        { p7, back, uv01 },
        { p3, back, uv00 },
        { p2, back, uv10 },

        // Right
        { p5, right, uv11 },
        { p6, right, uv01 },
        { p2, right, uv00 },
        { p1, right, uv10 },

        // Top
        { p7, up, uv11 },
        { p6, up, uv01 },
        { p5, up, uv00 },
        { p4, up, uv10 }
    };

    GLuint indices[] =
    {
        // Bottom
        3, 1, 0, 3, 2, 1,

        // Left
        3 + 4 * 1, 1 + 4 * 1, 0 + 4 * 1,
        3 + 4 * 1, 2 + 4 * 1, 1 + 4 * 1,

        // Front
        3 + 4 * 2, 1 + 4 * 2, 0 + 4 * 2,
        3 + 4 * 2, 2 + 4 * 2, 1 + 4 * 2,

        // Back
        3 + 4 * 3, 1 + 4 * 3, 0 + 4 * 3,
        3 + 4 * 3, 2 + 4 * 3, 1 + 4 * 3,

        // Right
        3 + 4 * 4, 1 + 4 * 4, 0 + 4 * 4,
        3 + 4 * 4, 2 + 4 * 4, 1 + 4 * 4,

        // Top
        3 + 4 * 5, 1 + 4 * 5, 0 + 4 * 5,
        3 + 4 * 5, 2 + 4 * 5, 1 + 4 * 5,
    };

    return create_mesh(vertices, 24, indices, 36, attributes, 3);
}

mesh create_mesh_quad2d(const float2& min, const float2& max)
{
    vertex_attribute attributes[] = { { GL_FLOAT_VEC4, GL_FALSE }, { GL_FLOAT_VEC4, GL_TRUE }, { GL_FLOAT_VEC2, GL_FALSE } };

    float4 forward = { 0, 0, 1, 0 };

    vertex_default vertices[] =
    {
        { { min.x, min.y, 0.0f, 1.0f }, forward, { 0.0f, 0.0f } },
        { { min.x, max.y, 0.0f, 1.0f }, forward, { 0.0f, 1.0f } },
        { { max.x, max.y, 0.0f, 1.0f }, forward, { 1.0f, 1.0f } },
        { { max.x, min.y, 0.0f, 1.0f }, forward, { 1.0f, 0.0f } },
    };

    GLuint indices[] =
    {
        0,1,2,
        2,3,0
    };

    return create_mesh(vertices, 4, indices, 6, attributes, 3);
}
