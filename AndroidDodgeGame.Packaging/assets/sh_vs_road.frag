#version 300 es

uniform highp float pk_Distance;

mediump vec3 HSVToRGB(highp vec3 c)
{
	mediump vec4 k = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	mediump vec3 p = abs(fract(c.xxx + k.xyz) * 6.0 - k.www);
	return c.zzz * mix(k.xxx, clamp(p - k.xxx, 0.0, 1.0), c.y);
}

in highp vec3 vs_TEXCOORD0;
layout(location = 0) out mediump vec4 SV_Target0;
void main()
{
    highp vec3 uv = vs_TEXCOORD0;
    highp vec2 yval = vec2(abs(uv.y - 0.5), 0.0);
    highp vec2 xadd = vec2(pow(uv.z * 0.0225, 1.5), 0.0);
    highp vec2 xblur = vec2(mix(0.5, 0.8, clamp(uv.z * 0.1, 0.0, 1.0)), 0.0);
    highp vec3 xlin = step(vec3(0.025, 0.2, 0.4), yval.xxx);
    xlin.x = 1.0 - xlin.x;

    highp vec2 xval = uv.xx * vec2(0.25, 1.0) - yval.xx * vec2(0.25, 1.0) + vec2(0.0, 0.5);

    xval = fract(xval);
    xval = smoothstep(1.0 - xval, vec2(0.05), xblur.xx);

    xadd.x += xval.y * xlin.z;
    xval.x = xval.x * xlin.y + xlin.x;

    mediump vec3 color = vec3(0.0);
    color += HSVToRGB(vec3(pk_Distance * 0.001, 1.0, xval.x));
    color += xadd.xxx;

	SV_Target0 = vec4(color, 1.0);
}