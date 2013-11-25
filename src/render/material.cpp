#include "material.h"

Material::Material(Shader* shader_) : shader(shader_) {
    materialColour = glm::vec4(1.0, 1.0, 1.0, 0.0);
}

Material::~Material() {
    ClearTextures();
}

Shader* Material::Bind() {
    glEnable(GL_DEPTH_TEST);

    shader->Use();

    vector<Texture*>::iterator it;
    for(it = textures.begin(); it != textures.end(); ++it) {
        (*it)->Bind();
        shader->SendUniform((*it)->GetName(), (*it));
    }
    
    shader->SendUniform("materialColour", materialColour);

	return shader;
}

void Material::SetColour(glm::vec4& colour) {
    materialColour = colour;
}

void Material::AddTexture(Texture* texture) {
    if(texture != NULL && find(textures.begin(), textures.end(), texture) == textures.end()) {
        textures.push_back(texture);
    }
}

void Material::ClearTextures() {
    vector<Texture*>::iterator it;
    for(it = textures.begin(); it != textures.end(); ++it) {
        delete (*it);
    }
    textures.clear();
}

void Material::UnBind() {
	glUseProgram(0);
}
