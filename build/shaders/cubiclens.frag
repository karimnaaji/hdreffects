#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

float k = -0.45;
float dispersion = 0.01;
float scale = 0.9;
float etaR = 0.9, etaG = 0.6, etaB = 0.2;
float kcube = 0.5;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 eta = vec3(1.0 + dispersion * etaR, 1.0 + dispersion * etaG, 1.0 + dispersion * etaB);
    vec3 color = vec3(0.0); 

    float r2 = (uv.x - 0.5) * (uv.x - 0.5) + (uv.y - 0.5) * (uv.y - 0.5);   
    float f = 1 + r2 * (k + kcube * sqrt(r2));

    vec2 ruv = (f * eta.r) * scale * (uv.xy - 0.5) + 0.5;
    vec2 guv = (f * eta.g) * scale * (uv.xy - 0.5) + 0.5;
    vec2 buv = (f * eta.b) * scale * (uv.xy - 0.5) + 0.5;

    color.r = texture(renderTexture, ruv).r;
    color.g = texture(renderTexture, guv).g;
    color.b = texture(renderTexture, buv).b;

    float d = length(uv - vec2(0.5));
    color *= clamp(1.0 - d*d, 0.0, 1.0);

    outColour = vec4(color, 1.0);
}
