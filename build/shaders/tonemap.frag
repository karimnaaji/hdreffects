#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform sampler2D sampler;
uniform vec2 resolution;
uniform float time;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

float midGrey = 10.0;
float lmax = 12.0;
const float epsilon = 0.0001;

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(renderTexture, uv).rgb;

    float lavg = texture(sampler, vec2(0.5, 0.5)).r;
    float l = luminance(color);
    float ls = (l * midGrey) / (lavg + epsilon);
    float lc = (ls * (1+(ls / (lmax*lmax)))) / (1+ls);
    
    //if(uv.x > 0.5001) {
        outColour = vec4(lc * color, 1.0);
    //} else if(uv.x < 0.4992) {
    //    outColour = vec4(color, 1.0);
    //} else {
    //    outColour = vec4(0.5, 0.38, 1.0, 1.0);
    //}
}

