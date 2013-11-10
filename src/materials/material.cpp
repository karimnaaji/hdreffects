#include "material.h"

Material::Material(Shader* shader_) : shader(shader_) {
    materialColour = glm::vec4(1.0, 1.0, 1.0, 0.0);
}

Material::~Material() {}

Shader* Material::Bind() {
    glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->Program());

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
    if(texture != NULL && std::find(textures.begin(), textures.end(), texture) == textures.end()) {
        textures.push_back(texture);
    }
}

void Material::UnBind() {
	glUseProgram(0);
}
