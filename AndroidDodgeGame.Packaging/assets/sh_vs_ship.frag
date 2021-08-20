#version 300 es

uniform highp float pk_Time;
uniform highp float pk_Distance;

mediump vec3 HSVToRGB(highp vec3 c)
{
	mediump vec4 k = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	mediump vec3 p = abs(fract(c.xxx + k.xyz) * 6.0 - k.www);
	return c.zzz * mix(k.xxx, clamp(p - k.xxx, 0.0, 1.0), c.y);
}

in mediump vec3 vs_TEXCOORD0;
layout(location = 0) out mediump vec4 SV_Target0;
void main()
{
	mediump vec2 uv = vs_TEXCOORD0.zy;

	uv.y -= 1.0;
	uv.x -= 1.0;

	highp float grad = 1.0 - fract((uv.x * uv.y) * 0.01f + pk_Time * 0.15f);
	highp float gradc = 1.0 - fract((uv.x * uv.y) * 0.035f + pk_Time * 0.35f);

	grad *= grad;

	gradc = smoothstep(gradc, 0.8, 0.2);

	mediump vec3 color = mix(vec3(grad * 0.8 + 0.15), HSVToRGB(vec3(pk_Distance * 0.001 + 0.05, 0.8, 1.5)), gradc);

	SV_Target0 = vec4(color, 1.0f);
}