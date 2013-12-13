#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    float l = luminance(texture(renderTexture, uv).rgb);
    outColour = vec4(l, 1.0, 1.0, 1.0);
}
