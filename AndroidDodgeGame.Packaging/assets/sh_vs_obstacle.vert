#version 300 es

uniform highp float pk_Distance;
uniform highp mat4 pk_MATRIX_M;
uniform highp mat4 pk_MATRIX_VP;

layout(location = 0) in vec3 in_POSITION0;
layout(location = 1) in vec3 in_NORMAL0;
layout(location = 2) in vec2 in_TEXCOORD0;

out mediump vec2 vs_TEXCOORD0;

highp vec2 xyoffset(highp float vz, float dist)
{
    vz = max(0.0f, vz);
    dist *= 0.25;
    float yoffset = pow(vz * 0.03, 2.0);
    float offsetamount = pow(vz, 1.5) * 0.015;

    float xoffset = sin(vz * 0.05 + dist * 0.1) * offsetamount * 0.5;
    xoffset += sin(vz * 0.025 + dist * 0.13457) * offsetamount * 0.35;
    xoffset += pow(vz * 0.01, 3.0) * 20.0;
    yoffset += cos(vz * 0.03 + dist * 0.0625) * offsetamount * 0.15;

    return vec2(xoffset, yoffset);
}

void main()
{
	highp vec4 worldposition = pk_MATRIX_M * vec4(in_POSITION0, 1.0);
    worldposition.xy += xyoffset(worldposition.z, pk_Distance);

	gl_Position = pk_MATRIX_VP * worldposition;
	vs_TEXCOORD0 = in_POSITION0.xy;
}