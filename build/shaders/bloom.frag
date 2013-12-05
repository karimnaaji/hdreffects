#version 150

out vec4 outColour;

uniform sampler2D tex;
uniform sampler2D bloom;
uniform vec2 resolution;
uniform float bloomFactor;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(tex, uv).rgb;
    vec3 colorBloom = texture(bloom, uv).rgb;

    color += colorBloom * bloomFactor;
    //float exposure = 0.9;
    //float brightThreshold = 0.5;
    //float Y = dot(vec3(0.30, 0.59, 0.11), color.rgb);
    //float YD = exposure * (exposure/brightThreshold + 1.0) / (exposure + 1.0);
    //color *= YD;

    outColour = vec4(color, 1.0);
}
