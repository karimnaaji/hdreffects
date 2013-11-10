#version 150

in vec3 position;
in vec4 colour;
in vec2 uv;
in vec3 normal;

uniform float globalTime;
uniform mat4 mvp;
uniform mat3 normalMatrix;
uniform vec3 camPosition;

const float etaR = 0.65;
const float etaG = 0.67;
const float etaB = 0.69;
const float fresnelPower = 5.0;

const float f = ((1.0-etaG)*(1.0-etaG)) / ((1.0+etaG)*(1.0+etaG));

out vec3 reflect;
out vec3 refractR;
out vec3 refractG;
out vec3 refractB;
out float ratio;

void main() {
    vec4 ecPosition = mvp * vec4(position, 1);
    vec3 ecPosition3 = ecPosition.xyz / ecPosition.w;

    vec3 i = normalize(ecPosition3);
    vec3 n = normalize(normalMatrix * normal);

    ratio = f + (1.0 - f) * pow((1.0 - dot(-i,n)), fresnelPower);
    refractR = refract(i, n, etaR);
    refractG = refract(i, n, etaG);
    refractB = refract(i, n, etaB);
    reflect = reflect(i, n);

    gl_Position = mvp * vec4(position, 1);
}
