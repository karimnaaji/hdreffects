#version 150

out vec4 outColour;

uniform sampler2D tex;
uniform sampler2D bloom;
uniform vec2 resolution;
uniform int addNoise;
uniform float time;
uniform float bloomFactor;

mat2 m = mat2(0.8, 0.6, -0.6, 0.8);

float hash(vec2 p) {
	float h = dot(p,vec2(127.1,311.7));
    return -1.0 + 2.0*fract(sin(h)*43758.5453123);
}

float noise(in vec2 p) {
    vec2 i = floor(p);
    vec2 f = fract(p);
	vec2 u = f*f*(3.0-2.0*f);
    return mix(mix(hash(i + vec2(0.0,0.0)), 
                   hash(i + vec2(1.0,0.0)), u.x),
               mix(hash(i + vec2(0.0,1.0)), 
                   hash(i + vec2(1.0,1.0)), u.x), u.y);
}

float fbm(vec2 p) {
	float f = 0.0;
	f += 0.5000 * noise(p); p *= 2.02;
	f += 0.2500 * noise(p); p *= 2.03;
	f += 0.1250 * noise(p); p *= 2.01;
	f += 0.0625 * noise(p); p *= 2.04;
	f /= 0.9375; 
	return f;
}

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

const float noiseSeed = 20.0;
const float noiseStrength = 0.3;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(tex, uv).rgb;
    vec3 colorBloom = texture(bloom, uv).rgb;

    if(addNoise == 1) {
		float f = fbm(vec2(noiseSeed * uv));
		colorBloom += noiseStrength * luminance(colorBloom) * abs(f);
	} 

    outColour = vec4(color + colorBloom * bloomFactor, 1.0);
}
