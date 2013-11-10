#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics.h"
#include <string>

class Texture {
    public:
        Texture(string name);
        virtual ~Texture();

        virtual void Load(string filename) = 0;
        virtual GLuint Bind();
        GLuint TextureId() const;
        GLuint TextureIndex() const;
        string GetName() const;
    protected:
        GLuint textureIndex;
        GLuint textureId;

        GLenum Format;
        GLenum Type;
        GLenum InternalFormat;

        float* data;
        virtual void Generate();
    private:
        string name;
};

#endif
