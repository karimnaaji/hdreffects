#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics.h"
#include "texture.h"
#include "shader.h"

class Framebuffer {
    public:
        Framebuffer(int width, int height, bool depth = false);
        ~Framebuffer();

        void Start() const;
        void End() const;
        void Bind(Shader* shader) const;
        void Init();
        void Clear() const;
        void AttachTexture(Texture* renderTexture);
        void Resize(int width, int height);
    private:
        int width, height;
        Texture* renderTexture;
        bool depth;
        GLuint id;
        GLuint depthId;
};

#endif
