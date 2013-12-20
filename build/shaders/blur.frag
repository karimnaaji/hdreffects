#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec2 texelSize = 1.0 / resolution;
    vec4 color = vec4(0.0);
    
    color +=  3.0 * texture(renderTexture, uv);
    color +=  2.0 * texture(renderTexture, uv + vec2( texelSize.x,          0.0));
    color +=  2.0 * texture(renderTexture, uv + vec2(-texelSize.x,          0.0));
    color +=  2.0 * texture(renderTexture, uv + vec2(         0.0,  texelSize.y));
    color +=  2.0 * texture(renderTexture, uv + vec2(         0.0, -texelSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2( texelSize.x,  texelSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2(-texelSize.x,  texelSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2(-texelSize.x, -texelSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2( texelSize.x, -texelSize.y));
    color /= 16.0;

    outColour = color;
}
