#include "framebuffer.h"

Framebuffer::Framebuffer(int width_, int height_, bool depth_) {
    id = 0;
    depth = depth_;
    width = width_;
    height = height_;
}

Framebuffer::~Framebuffer() {
    glDeleteRenderbuffers(1, &depthId);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &id);
}

void Framebuffer::Resize(int width, int height) {
    // TODO resize frame buffer and texture
}

void Framebuffer::Start() const {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    Clear();
}

void Framebuffer::End() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Bind(Shader* shader) const {
    // TODO : move this to renderer
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
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture->TextureId(), 0);

    // TODO : make a test if we want depth testing to take place to this fbo
    glGenRenderbuffers(1, &depthId);
    glBindRenderbuffer(GL_RENDERBUFFER_EXT, depthId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthId);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
