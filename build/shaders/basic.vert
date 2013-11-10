#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;
in vec3 normal;

uniform float globalTime;
uniform mat4 mvp;
uniform mat3 normalMatrix;

out vec3 norm;

void main() {
    norm = normalize(normalMatrix * normal);
    gl_Position = mvp * vec4(position, 1);
}
