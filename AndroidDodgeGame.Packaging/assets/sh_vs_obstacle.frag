#version 300 es

uniform highp float pk_Time;
uniform mediump vec4 pk_Color;

in mediump vec2 vs_TEXCOORD0;
layout(location = 0) out mediump vec4 SV_Target0;

void main()
{
	SV_Target0 = vec4(pk_Color.rgb * (smoothstep(fract(pk_Time * 2.5 + pk_Color.a), 0.5, 0.9) + 0.5), 1.0f);
}