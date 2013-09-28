#include "renderer.h"

Renderer::Renderer(int width, int height, Camera* camera_) {
    triangle = Mesh::Triangle();

    string vertex = "basic.vert";
    string fragment = "basic.frag";
    shader = new Shader(vertex, fragment);

    camera = camera_;
}

Renderer::~Renderer() {
  	delete shader;
  	delete triangle;
}

void Renderer::Init() {
    glClearColor(0.1, 0.1, 0.2, 1.0);

    shader->Link();
}

void Renderer::Render() {
    float time = (float) clock() / (CLOCKS_PER_SEC / 1000);

    glUseProgram(shader->Program());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUniform1f(glGetUniformLocation(shader->Program(), "globalTime"), time);
    glUniformMatrix4fv(glGetUniformLocation(shader->Program(), "view"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    triangle->Draw();

    glUseProgram(0);
}

void Renderer::CreateFrameBuffer(GLuint renderTexture) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // attach the render texture to the frame buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Renderer::CreateTexture(int width, int height, bool isDepth) {
    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLenum internalFormat = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA8;
    GLenum format = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, NULL);                

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}