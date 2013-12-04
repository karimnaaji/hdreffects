#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform vec2 resolution;
uniform float bloomFactor;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(renderTexture, uv).rgb;
    outColour = vec4(1.0);
}
