#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform sampler2D sampler;
uniform vec2 resolution;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

float midGrey = 0.6;
float lmax = 16.0;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(renderTexture, uv).rgb;

    float lavg = texture(sampler, vec2(0.5, 0.5)).r;
    float l = luminance(color);
    float ls = (l * midGrey) / lavg;
    float lc = (ls * (1+(ls / (lmax*lmax)))) / (1+ls);
    //float lc = 1.0;
    
    //float exposure = 3.5;
    //float brightThreshold = 4.0;
    //float YD = exposure * (exposure/brightThreshold + 1.0) / (exposure + 1.0);
    //color *= YD;
    //outColour = vec4(color, 1.0);
    outColour = vec4(lc * color, 1.0);
    //outColour = vec4(vec3(lavg), 1.0);
}

