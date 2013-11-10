#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;
in vec3 normal;

uniform float globalTime;
uniform mat4 mvp;

out vec3 norm;

void main() {
    mat3 normalMatrix = transpose(inverse(mat3(mvp)));
    norm = normalize(normalMatrix * normal);
    gl_Position = mvp * vec4(position, 1);
}
