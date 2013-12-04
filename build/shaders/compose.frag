#version 150

uniform sampler2D texHighRes;
uniform sampler2D blurLowRes;
uniform vec2 resolution;

out vec4 outColour;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec4 colorTexHR = texture(texHighRes, uv);
    vec4 colorTexLR = texture(blurLowRes, uv);

    outColour = vec4(colorTexHR.rgb + colorTexLR.rgb, 1.0);
}
