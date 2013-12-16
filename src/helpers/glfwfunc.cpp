#include "glfwfunc.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == 'B' && action == GLFW_RELEASE) {
        doBloom = !doBloom;
    }
    if(key == 'T' && action == GLFW_RELEASE) {
        doToneMapping = !doToneMapping;
    }
    if(key == 'R' && action == GLFW_RELEASE) {
        doCubicLens = !doCubicLens;
    }
    if(key == 'X' && action == GLFW_RELEASE) {
        Debug::Instance() << addNoise << std::endl;
        addNoise = !addNoise;
    }
    if(key == 'N') {
        brightThreshold += 0.01f;
        Debug::Instance() << brightThreshold << std::endl;
    }
    if(key == 'J') {
        brightThreshold -= 0.01f;
        brightThreshold = brightThreshold < 0.0f ? 0.0f : brightThreshold;
        Debug::Instance() << brightThreshold << std::endl;
    }
    if(key == 'V') {
        bloomFactor += 0.01f;
        bloomFactor = bloomFactor > 1.0f ? 1.0f : bloomFactor;
        Debug::Instance() << bloomFactor << std::endl;
    }
    if(key == 'G') {
        bloomFactor -= 0.01f;
        bloomFactor = bloomFactor < 0.0f ? 0.0f : bloomFactor;
        Debug::Instance() << bloomFactor << std::endl;
    }
    if(key == 'C' && action == GLFW_RELEASE) {
        blurPass++;
        Debug::Instance() << blurPass << std::endl;
    }
    if(key == 'F' && action == GLFW_RELEASE) {
        blurPass--;
        blurPass = blurPass < 0 ? 0 : blurPass;
        Debug::Instance() << blurPass << std::endl;
    }
}
