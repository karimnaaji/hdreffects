#include "texture.h"

Texture::Texture(string name_) : Format(GL_RGB), Type(GL_FLOAT), InternalFormat(GL_RGB8) {
    textureIndex = 0;
    name = name_;
}

Texture::Texture(string name_, int width_, int height_) : Format(GL_RGB), Type(GL_FLOAT), InternalFormat(GL_RGB8) {
    textureIndex = 0;
    name = name_;
    width = width_;
    height = height_;
}

Texture::~Texture() {
    glDeleteTextures(1, &textureIndex);
}

void Texture::Load(string filename) {
    // TODO later
}

GLuint Texture::TextureId() const {
    return textureId;
}

GLuint Texture::TextureIndex() const {
    return textureIndex;
}

string Texture::GetName() const {
    return name;
}

void Texture::Resize(int width_, int height_) {
    width = width_;
    height = height_;

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, Type, NULL);
}

GLuint Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    return textureIndex;
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Generate() {
    glGenTextures(1, &textureIndex);

    Bind();
        glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, Type, NULL);                
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Unbind();
}
