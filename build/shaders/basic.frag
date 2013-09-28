#version 150

in Vertex {
	vec4 colour;
	vec2 uv;
} IN;

out vec4 out_colour;

void main(void) {
    out_colour = IN.colour;
}