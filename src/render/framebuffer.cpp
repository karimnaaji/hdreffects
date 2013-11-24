#include "framebuffer.h"

Framebuffer::Framebuffer(bool depth_) {
    id = 0;
    depth = depth_;
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &id);
}

void Framebuffer::Bind(Shader* shader) const {
    shader->Use();
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    renderTexture->Bind();
    shader->SendUniform(renderTexture->GetName(), renderTexture);
}

void Framebuffer::Unbind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Clear() {
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
