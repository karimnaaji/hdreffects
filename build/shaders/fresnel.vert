#version 150

in vec3 position;
in vec3 normal;

uniform mat4 mvp;
uniform vec3 camPosition;

const float etaR = 0.64;
const float etaG = 0.65;
const float etaB = 0.66;
const float fresnelPower = 6.0;

const float f = ((1.0-etaG)*(1.0-etaG)) / ((1.0+etaG)*(1.0+etaG));

out vec3 reflect;
out vec3 refractR;
out vec3 refractG;
out vec3 refractB;
out float ratio;

void main() {
    vec3 i = normalize(position - camPosition);

    ratio = f + (1.0 - f) * pow((1.0 - dot(-i,normal)), fresnelPower);

    refractR = refract(i, normal, etaR);
    refractG = refract(i, normal, etaG);
    refractB = refract(i, normal, etaB);

    reflect = reflect(i, normal);

    gl_Position = mvp * vec4(position, 1);
}
