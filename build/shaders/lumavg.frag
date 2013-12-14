#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec2 texelSize = 1.0 / resolution;
    float l = 0.0;
    
    l += texture(renderTexture, uv).r;
    l += texture(renderTexture, uv + vec2(texelSize.x,         0.0)).r;
    l += texture(renderTexture, uv + vec2(        0.0, texelSize.y)).r;
    l += texture(renderTexture, uv + vec2(texelSize.x, texelSize.y)).r;

    l = l / 4.0;

    outColour = vec4(l, 1.0, 1.0, 1.0);
}
