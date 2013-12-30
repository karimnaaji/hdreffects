#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

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

void main() {
    vec2 uv = gl_FragCoord.xy / resolution; 
    vec2 p = -1.0 + 2.0 * uv;
    vec4 color = texture(renderTexture, uv);
            
    float r = dot(p, p);
    float a = atan(p.y, p.x);
    float f = fbm(vec2(r, 50.0 * a));
    float w = length(vec2(0.5) - uv);

    f *= w;

    outColour = mix(color, color * f, 0.4);
}
