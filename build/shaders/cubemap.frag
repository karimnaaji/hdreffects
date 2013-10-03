#version 150

in vec3 pos;

uniform samplerCube cubeMap;

out vec4 out_colour;

void main(void) {
    out_colour = texture(cubeMap, pos);
}
