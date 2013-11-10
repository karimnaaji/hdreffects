#version 150

in vec3 r;
out vec4 out_colour;

uniform samplerCube cubeMap;

void main(void) {
    out_colour = texture(cubeMap, r);
}
