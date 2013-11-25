#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform vec2 resolution;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    
    vec4 colour = texture(renderTexture,uv);
    outColour = colour;
}
