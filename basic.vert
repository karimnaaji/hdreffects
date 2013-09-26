#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;

uniform float globalTime;
uniform mat4 view;

out Vertex {
	vec4 colour;
	vec2 uv;
} OUT;

void main() {
	OUT.uv = uv;
	OUT.colour = colour;
	
    gl_Position = view * vec4(position, 1);
}