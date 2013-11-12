#version 150

out vec4 outColour;

void main(void) {
    vec2 resolution = vec2(960, 680);
    vec2 uv = gl_FragCoord.xy / resolution;
    
    float vignette = length(uv - vec2(0.5));
    vec4 colour = vec4(0.0, 0.0, 0.0, 1.0);
    colour *= clamp(1.0 - vignette, 0.0, 1.0);
    outColour = colour;
}
