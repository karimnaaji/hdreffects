#version 150

out vec4 outColour;

uniform sampler2D renderTexture;
uniform vec2 resolution;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));
}

float midgrey = 0.6;
float maxlum = 16.0;
vec3 lumWeight = vec3(0.299, 0.587, 0.114);

void main(void) {
    vec2 uv = gl_FragCoord.xy / resolution;
    vec3 color = texture(renderTexture, uv).rgb;
    outColour = vec4(color * vec3(0.0, 1.0, 0.0), 1.0);
    //outColour = vec4(uv, 1.0, 1.0);

    /*
    float lumAvg = luminance(texture(renderTexture, vec2(0.5,0.5)).rgb);
    float lum = dot(color, lumWeight);
    float lumScaled = (lum * midgrey) / lumAvg;
    float lumCompressed = (lumScaled*(1+(lumScaled/(maxlum*maxlum)))) / (1+lumScaled);
    outColour = vec4(color, 1.0); //vec4(lumCompressed * color, 1.0);
    */

    /*
    vec4 colour = texture(renderTexture,uv);
    float l = luminance(colour.xyz);

    if(l > 1.2)
        outColour = vec4(vec3(l),1.0);
    else 
        outColour = vec4(0.0, 0.0, 0.0, 1.0);
    */
}
