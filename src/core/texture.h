#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics.h"

class Texture {
    public:
        Texture();
        virtual ~Texture();

        virtual void Load(string filename) = 0;
        virtual GLuint Bind();
        GLuint TextureId() const;
        GLuint TextureIndex() const;
    protected:
        GLuint textureIndex;
        GLuint textureId;

        GLenum Format;
        GLenum Type;
        GLenum InternalFormat;

        float* data;
        virtual void Generate();
};

#endif
