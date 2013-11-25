#include "framebuffer.h"

Framebuffer::Framebuffer(int width_, int height_, bool depth_) {
    id = 0;
    depth = depth_;
    width = width_;
    height = height_;
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &id);
}

void Framebuffer::Resize(int width, int height) {
    // TODO resize frame buffer and texture
}

void Framebuffer::Start() const {
    Clear();
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void Framebuffer::End() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind(Shader* shader) const {
    shader->Use();
    renderTexture->Bind();
    shader->SendUniform(renderTexture->GetName(), renderTexture);
    shader->SendUniform("resolution", glm::vec2(width, height));
    shader->Release();
}

void Framebuffer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::AttachTexture(Texture* renderTexture_) {
    renderTexture = renderTexture_;
}

void Framebuffer::Init() {
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture->TextureId(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
