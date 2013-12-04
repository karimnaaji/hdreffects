#version 150

uniform sampler2D renderTexture;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec2 pSize = vec2(1.0 / resolution.x, 1.0 / resolution.y);
    vec4 color = vec4(0.0);

    color += 3.0 * texture(renderTexture, uv);
    color += 2.0 * texture(renderTexture, uv + vec2( pSize.x, 0.0));
    color += 2.0 * texture(renderTexture, uv + vec2(-pSize.x, 0.0));
    color += 2.0 * texture(renderTexture, uv + vec2(0.0,  pSize.y));
    color += 2.0 * texture(renderTexture, uv + vec2(0.0, -pSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2(pSize.x, pSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2(-pSize.x,  pSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2(-pSize.x, -pSize.y));
    color += 1.25 * texture(renderTexture, uv + vec2( pSize.x, -pSize.y));
                                                    
    outColour = color / 16.0;
}
