#version 300 es

uniform highp float pk_Time;
uniform highp mat4 pk_MATRIX_M;
uniform highp mat4 pk_MATRIX_VP;

layout(location = 0) in vec3 in_POSITION0;

out mediump vec3 vs_TEXCOORD0;

void main()
{
	highp vec4 worldposition = pk_MATRIX_M * vec4(in_POSITION0, 1.0);
	gl_Position = pk_MATRIX_VP * worldposition;
	vs_TEXCOORD0 = in_POSITION0;
}