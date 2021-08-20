#version 300 es

uniform highp float pk_Distance;

mediump vec3 HSVToRGB(highp vec3 c)
{
	highp vec4 k = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
	highp vec3 p = abs(fract(c.xxx + k.xyz) * 6.0 - k.www);
	return c.zzz * mix(k.xxx, clamp(p - k.xxx, 0.0, 1.0), c.y);
}

in highp vec2 vs_TEXCOORD0;
layout(location = 0) out mediump vec4 SV_Target0;
void main()
{
	highp vec2 uv = vs_TEXCOORD0;
	uv.x -= 1.075;
	uv.y -= 1.075;
	uv *= 10.0;	
	uv /= dot(uv,uv);

	uv = 1.0 - uv;
	
	highp float sdist = pk_Distance * 0.01f;
	highp float offs = 0.5 + sin(sdist * 0.05) * 0.5;
    highp float rdist = length(uv);
	rdist *= 2.7 - rdist;
	rdist *= 4.5 - rdist;
	
	rdist += sin(2.0 - uv.x * 3.0) * (5.0 - rdist) * 0.25;
	rdist += sin(2.5 - uv.y * 4.0) * (5.0 - rdist) * 0.25;
	rdist += cos((1.0 - uv.x) * 10.0 - 0.5) * 0.4 * offs;

    highp float udist = rdist * 2.0 - sdist * 0.5;

	highp float cdist = udist - sdist * 0.15;

	highp float cgrad = smoothstep(fract(cdist), 0.2, 0.9);

    highp float grad = fract(udist);
	grad *= grad;

	mediump vec3 color = mix(vec3(grad), HSVToRGB(vec3(pk_Distance * 0.001, 1,1)), cgrad);
	SV_Target0 = vec4(color, 1.0f);
}