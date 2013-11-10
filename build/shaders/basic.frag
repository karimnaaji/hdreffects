#version 150

in vec3 norm;
out vec4 out_colour;

//uniform samplerCube cubeMap;

void main(void) {
    out_colour = vec4(-norm, 1);
}
