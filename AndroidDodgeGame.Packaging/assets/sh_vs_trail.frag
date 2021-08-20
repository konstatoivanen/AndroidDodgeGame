#version 300 es

uniform highp float pk_Time;
uniform highp float pk_Distance;

mediump vec3 HSVToRGB(highp vec3 c)
{
	mediump vec4 k = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	mediump vec3 p = abs(fract(c.xxx + k.xyz) * 6.0 - k.www);
	return c.zzz * mix(k.xxx, clamp(p - k.xxx, 0.0, 1.0), c.y);
}

in mediump float vs_TEXCOORD0;
layout(location = 0) out mediump vec4 SV_Target0;
void main()
{
	highp float yv = abs(vs_TEXCOORD0);
	highp float iyv = clamp(0.5 / (yv + 0.001), 0.0, 1.0);

	mediump float gradc = smoothstep(1.0 - fract(yv * 0.5f - pk_Time), 0.5, 0.2);
	mediump vec3 color = HSVToRGB(vec3(pk_Distance * 0.001 + 0.05, gradc, 1.5 * (iyv * iyv * iyv + 0.5)));

	SV_Target0 = vec4(color, 1.0);
}