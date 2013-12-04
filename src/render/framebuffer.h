#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "graphics.h"
#include "texture.h"
#include "shader.h"

class Framebuffer {
    public:
        Framebuffer(int width, int height, bool depth = false);
        ~Framebuffer();

        void Start(float downSamplingRatio = 1.0);
        void End();
        void Bind(Shader* shader, glm::vec2 resolution, string textureName) const;
        void Bind(Shader* shader, string textureName) const;
        void Bind(Shader* shader, glm::vec2 resolution) const;
        void Bind(Shader* shader) const;
        void Init();
        void Clear() const;
        void AttachTexture(Texture* renderTexture);
        void Resize(int width, int height);
        void Upscale(float ratio);
        int Width() const;
        int Height() const;
        Texture* GetRenderTexture() const;
    private:
        void ScaleRenderTarget(float ratio);
        int width, height;
        Texture* renderTexture;
        bool depth;
        GLuint id;
        GLuint depthId;
        float currentSampleRatio;
};

#endif
