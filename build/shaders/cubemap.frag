#version 150

in vec3 pos;

uniform samplerCube cubeMap;

out vec4 outColour;

void main(void) {
    vec4 color = texture(cubeMap, pos);
    outColour = color;
}

