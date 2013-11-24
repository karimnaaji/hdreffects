#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics.h"
#include <string>

class Texture {
    public:
        Texture(string name);
        Texture(string name, int width, int height);
        virtual ~Texture();

        virtual void Load(string filename);
        virtual GLuint Bind();
        void Unbind();
        GLuint TextureId() const;
        GLuint TextureIndex() const;
        string GetName() const;
        void Resize(int width, int height);
    protected:
        GLuint textureIndex;
        GLuint textureId;

        GLenum Format;
        GLenum Type;
        GLenum InternalFormat;

        float* data;
        virtual void Generate();
        int width, height;
        string name;
};

#endif
