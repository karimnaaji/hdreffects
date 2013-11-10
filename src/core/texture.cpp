#include "texture.h"

Texture::Texture(string name_) : Format(GL_RGB), Type(GL_FLOAT), InternalFormat(GL_RGB8) {
    textureIndex = 0;
    name = name;
}

Texture::~Texture() {
    // TODO
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

GLuint Texture::Bind() {
    // TODO
    return 0;
}

void Texture::Generate() {
    // TODO
}
