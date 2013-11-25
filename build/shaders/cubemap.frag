#version 150

in vec3 pos;

uniform samplerCube cubeMap;

out vec4 out_colour;

float luminance(vec3 color) {
    return dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));;
}

void main(void) {
    vec4 color = texture(cubeMap, pos);
    float L = luminance(color.rgb);
   
    L = L / (L + 1);
    out_colour = color;
}

