#include "glfwfunc.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == 'B' && action == GLFW_RELEASE) {
        doBloom = !doBloom;
    } 
    if(key == 'N') {
        brightThreshold += 0.01f;
        brightThreshold = brightThreshold > 1.0f ? 1.0f : brightThreshold;
        std::cout << brightThreshold << std::endl;
    }
    if(key == 'J') {
        brightThreshold -= 0.01f;
        brightThreshold = brightThreshold < 0.0f ? 0.0f : brightThreshold;
        std::cout << brightThreshold << std::endl;
    }
    if(key == 'V') {
        bloomFactor += 0.01f;
        bloomFactor = bloomFactor > 1.0f ? 1.0f : bloomFactor;
        std::cout << bloomFactor << std::endl;
    }
    if(key == 'G') {
        bloomFactor -= 0.01f;
        bloomFactor = bloomFactor < 0.0f ? 0.0f : bloomFactor;
        std::cout << bloomFactor << std::endl;
    }
    if(key == 'C' && action == GLFW_RELEASE) {
        blurPass++;
        std::cout << blurPass << std::endl;
    }
    if(key == 'F' && action == GLFW_RELEASE) {
        blurPass--;
        blurPass = blurPass < 0 ? 0 : blurPass;
        std::cout << blurPass << std::endl;
    }
}
