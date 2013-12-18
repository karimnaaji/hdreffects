#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform sampler2D sampler;
uniform vec2 resolution;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

float a = 8.0;
float lmax = 16.0;
const float epsilon = 0.0001;

float lumCompressed(float lavg, float l) {
    float ls = (l * a) / (lavg + epsilon);
    return (ls * (1 + (ls / (lmax*lmax)))) / (1 + ls);
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(renderTexture, uv).rgb;

    float l = luminance(color);
    float lavg = texture(sampler, vec2(0.5, 0.5)).r;

    outColour = vec4(lumCompressed(lavg, l) * color, 1.0);
}
