#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;
uniform float threshold;

out vec4 outColour;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec4 colour = texture(renderTexture, uv);
    float l = luminance(colour.xyz);

    if(l > threshold) {
        outColour = vec4(vec3(l), 1.0);
    } else {
        outColour = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
