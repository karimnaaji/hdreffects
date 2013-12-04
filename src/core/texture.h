#ifndef TEXTURE_H
#define TEXTURE_H

#include "graphics.h"
#include <string>

class Texture {
    public:
        Texture(string name, GLuint textureIndex = 0);
        Texture(string name, int width, int height, GLint internalFormat, GLuint textureIndex = 0); 
        virtual ~Texture();

        virtual void Load(string filename);
        virtual GLuint Bind();
        virtual void Init();
        void Unbind();
        GLuint TextureId() const;
        GLuint TextureIndex() const;
        string GetName() const;
        void Resize(int width, int height);
        void SetTextureIndex(GLuint index);
    protected:
        GLuint TextureUnitFromIndex(GLuint index);
        GLuint textureIndex;
        GLuint textureId;

        GLenum Format;
        GLenum Type;
        GLenum InternalFormat;

        float* data;
        int width, height;
        string name;
};

#endif
