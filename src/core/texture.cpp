#include "texture.h"

Texture::Texture(string name_, GLuint textureIndex_) :
    Format(GL_RGBA),
    Type(GL_UNSIGNED_BYTE),
    InternalFormat(GL_RGB16F_ARB) {
    textureId = 0;
    name = name_;
    textureIndex = textureIndex_;
}

Texture::Texture(string name_, int width_, int height_, GLint internalFormat, GLuint textureIndex_) :
    Format(GL_RGBA),
    Type(GL_UNSIGNED_BYTE) {
    InternalFormat = internalFormat;
    textureId = 0;
    name = name_;
    width = width_;
    height = height_;
    textureIndex = textureIndex_;
}

Texture::~Texture() {
    DisposeGL();
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

void Texture::DisposeGL() {
    glDeleteTextures(1, &textureId);
}

void Texture::Resize(int width_, int height_) {
    width = width_;
    height = height_;

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, Type, NULL);
}

GLuint Texture::Bind() {
    glActiveTexture(TextureUnitFromIndex(textureIndex));
    glBindTexture(GL_TEXTURE_2D, textureId);
    return textureId;
}

void Texture::SetTextureIndex(GLuint index) {
    textureIndex = index;
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Init() {
    glGenTextures(1, &textureId);

    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, InternalFormat, width, height, 0, Format, Type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    Unbind();
}

void Texture::SetFiltering(GLint filtering) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering);
    Unbind();
}

GLuint Texture::TextureUnitFromIndex(GLuint index) {
    switch(index) {
    case 1:
        return GL_TEXTURE1;
    case 2:
        return GL_TEXTURE2;
    case 3:
        return GL_TEXTURE3;
    case 4:
        return GL_TEXTURE4;
    default:
        return GL_TEXTURE0;
    }
}
