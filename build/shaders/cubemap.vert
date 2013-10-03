#version 150

in vec3 position;

uniform mat4 mvp;
uniform vec3 camPosition;

out vec3 pos;

void main() {
    gl_Position = mvp * vec4(position + camPosition, 1);
    pos = position;
}
