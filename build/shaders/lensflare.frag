#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

int ghosts = 3;
float dispertion = 0.3;

out vec4 outColour;

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

vec3 pattern(vec2 uv) {
   vec2 p = -1.0 + 2.0 * uv;
   float p2 = dot(p,p);
   float a = atan(fract(0.5), fract(0.01));
   float f = fbm(vec2(15.0*p2,15.0*a)) / 2.0;
   float d = length(uv - vec2(0.5));
   float r = 0.2 + 0.6 * sin(12.5*length(uv - vec2(0.5)));
   float g = 0.2 + 0.6 * sin(20.5*length(uv - vec2(0.5)));
   float b = 0.2 + 0.6 * sin(17.2*length(uv - vec2(0.5)));
   return (1.0-f) * vec3(r,g,b);
}

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

void main() {
    vec2 uv = (-gl_FragCoord.xy / resolution)+vec2(1.0); 
    vec2 ghostDir = (vec2(0.5) - uv) * dispertion;

    vec4 result = vec4(0.0);
    for (int i = 0; i < ghosts; ++i) { 
        vec2 offset = fract(uv + ghostDir * float(i));
        float weight = length(vec2(0.5) - offset) / length(vec2(0.5));
        weight = pow(1.0 - weight, 10.0);
        result += texture(renderTexture, offset) * weight;
    }
    float patternWeight = 0.4 * length(vec2(0.5) - uv);
    result = mix(result, result * vec4(pattern(uv), 1.0), 0.6);

    vec2 haloVec = normalize(ghostDir) * 0.4;
    float weight = length(vec2(0.5) - fract(uv + haloVec)) / length(vec2(0.5));
    weight = pow(1.0 - weight, 5.0);
    vec4 halo = texture(renderTexture, uv + haloVec) * weight;

    outColour = 0.06 * result + 0.03 * halo;
}
