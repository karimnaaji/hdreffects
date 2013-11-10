#include "material.h"

Material::Material(Shader* shader_) : shader(shader_) {}

Material::~Material() {}

Shader* Material::Bind() {
    glEnable(GL_DEPTH_TEST);

	glUseProgram(shader->Program());
	return shader;
}

void Material::UnBind() {
	glUseProgram(0);
}
