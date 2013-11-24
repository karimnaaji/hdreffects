#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics.h"
#include "texture.h"
#include "shader.h"

class Framebuffer {
    public:
        Framebuffer(bool depth = false);
        ~Framebuffer();

        void Bind(Shader* shader) const;
        void Unbind() const;
        void Init();
        void Clear();
        void AttachTexture(Texture* renderTexture);
    private:
        Texture* renderTexture;
        bool depth;
        GLuint id;
};

#endif
