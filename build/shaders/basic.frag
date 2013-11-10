#version 150

in vec3 norm;
out vec4 out_colour;

void main(void) {
    out_colour = vec4(norm, 1);
}
