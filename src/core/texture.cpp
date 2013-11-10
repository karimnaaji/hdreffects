#include "texture.h"

Texture::Texture() : Format(GL_RGB), Type(GL_FLOAT), InternalFormat(GL_RGB8) {
    textureIndex = 0;
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

GLuint Texture::Bind() {
    // TODO
    return 0;
}

void Texture::Generate() {
    // TODO
}
