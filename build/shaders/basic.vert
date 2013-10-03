#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;

uniform float globalTime;
uniform mat4 mvp;

out Vertex {
	vec4 colour;
	vec2 uv;
} OUT;

void main() {
	OUT.uv = uv;
	OUT.colour = colour;
	
    gl_Position = mvp * vec4(position, 1);
}
