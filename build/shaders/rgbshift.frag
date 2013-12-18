#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

const float distortStrength = 4.0;
const float dispersion = 0.15;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution; 
    vec2 texelSize = 1.0 / resolution;

    vec2 direction = (vec2(0.5) - uv) * dispersion;
    vec3 distortion = vec3(-texelSize.x * distortStrength, 0.0, texelSize.x * distortStrength);

    distortion = vec3(0.6, 0.7, 0.8);
    vec4 rgbShift = vec4(
        texture(renderTexture, uv + direction * distortion.r).r,
        texture(renderTexture, uv + direction * distortion.g).g,
        texture(renderTexture, uv + direction * distortion.b).b,
        1.0
    );

    outColour = rgbShift;
}
