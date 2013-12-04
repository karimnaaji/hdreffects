#version 150

in vec3 position;

//uniform mat4 aamvp;

void main() {   
    gl_Position = vec4(position.xy, 0.0, 1.0);
}
