#version 150

in vec3 reflect;
in vec3 refractR;
in vec3 refractG;
in vec3 refractB;
in float ratio;
out vec4 outColour;

uniform samplerCube cubeMap;

void main(void) {
    vec3 refractColor, reflectColor;

    refractColor.r = vec3(texture(cubeMap, refractR)).r;
    refractColor.g = vec3(texture(cubeMap, refractG)).g;
    refractColor.b = vec3(texture(cubeMap, refractB)).b;
    reflectColor = vec3(texture(cubeMap, reflect));

    outColour = vec4(mix(refractColor, reflectColor, ratio), 1.0);
}
