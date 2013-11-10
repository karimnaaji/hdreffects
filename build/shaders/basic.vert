#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;
in vec3 normal;

uniform float globalTime;
uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform vec3 camPosition;

out vec3 r;

void main() {
    vec3 i = normalize(position - camPosition);
    vec3 norm = normalize(normalMatrix * normal);
    r = reflect(i, norm);

    gl_Position = mvp * vec4(position, 1);
}
