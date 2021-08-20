#version 300 es

layout(location = 0) in vec4 in_POSITION0;
layout(location = 1) in vec4 in_NORMAL0;
layout(location = 2) in vec2 in_TEXCOORD0;
out mediump vec2 vs_TEXCOORD0;

void main()
{
	gl_Position = in_POSITION0;
	vs_TEXCOORD0 = in_TEXCOORD0;
}