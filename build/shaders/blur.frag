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


// TODO : try this
/*
const float blurSizeH = 1.0 / 300.0;
const float blurSizeV = 1.0 / 200.0;
void main() {
    vec4 sum = vec4(0.0);
    for (int x = -4; x <= 4; x++)
    for (int y = -4; y <= 4; y++)
        sum += texture(
        texFramebuffer,
        vec2(Texcoord.x + x * blurSizeH, Texcoord.y + y * blurSizeV)
        ) / 81.0;
    outColor = sum;
}
*/
