#include "glfwfunc.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(key == 'L' && action == GLFW_RELEASE) {
        g_doLensFlare = !g_doLensFlare;
    }
    if(key == 'B' && action == GLFW_RELEASE) {
        g_doBloom = !g_doBloom;
    }
    if(key == 'T' && action == GLFW_RELEASE) {
        g_doToneMapping = !g_doToneMapping;
    }
    if(key == 'R' && action == GLFW_RELEASE) {
        g_doCubicLens = !g_doCubicLens;
    }
    if(key == 'X' && action == GLFW_RELEASE) {
        Debug::Instance() << g_addNoise << std::endl;
        g_addNoise = !g_addNoise;
    }
    if(key == 'N') {
        g_brightThreshold += 0.01f;
        Debug::Instance() << g_brightThreshold << std::endl;
    }
    if(key == 'J') {
        g_brightThreshold -= 0.01f;
        g_brightThreshold = g_brightThreshold < 0.0f ? 0.0f : g_brightThreshold;
        Debug::Instance() << g_brightThreshold << std::endl;
    }
    if(key == 'V') {
        g_bloomFactor += 0.01f;
        g_bloomFactor = g_bloomFactor > 1.0f ? 1.0f : g_bloomFactor;
        Debug::Instance() << g_bloomFactor << std::endl;
    }
    if(key == 'G') {
        g_bloomFactor -= 0.01f;
        g_bloomFactor = g_bloomFactor < 0.0f ? 0.0f : g_bloomFactor;
        Debug::Instance() << g_bloomFactor << std::endl;
    }
    if(key == 'C' && action == GLFW_RELEASE) {
        g_blurPass++;
        Debug::Instance() << g_blurPass << std::endl;
    }
    if(key == 'F' && action == GLFW_RELEASE) {
        g_blurPass--;
        g_blurPass = g_blurPass < 0 ? 0 : g_blurPass;
        Debug::Instance() << g_blurPass << std::endl;
    }
}
