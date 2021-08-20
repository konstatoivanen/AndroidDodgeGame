#pragma once
#include "graphics.h"
#include "pkmath.h"

mesh create_mesh_ship();
mesh create_mesh_pyramid(float width, float height);
mesh create_mesh_octahedron(float width, float height);
mesh create_mesh_wedge(float thickness, float size);
mesh create_mesh_cross(float thickness, float size);
mesh create_mesh_road(float width, float length, float edgewidth, float elevation, uint32_t segments);
mesh create_mesh_box(const float3& offset, const float3& extents);
mesh create_mesh_quad2d(const float2& min, const float2& max);