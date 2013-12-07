#version 150

uniform sampler2D sampler1;
uniform sampler2D sampler2;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec4 sampler1 = texture(sampler1, uv);
    vec4 sampler2 = texture(sampler2, uv);

    outColour = vec4(sampler1.rgb + sampler2.rgb, 1.0);
}
