#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    outColour = texture(renderTexture, uv);
}
