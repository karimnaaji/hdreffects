#include "materialcubemap.h"

MaterialCubeMap::MaterialCubeMap(Shader* shader, HDRTextureCube* hdrTextureCube_) : Material(shader), hdrTextureCube(hdrTextureCube_) {
    AddTexture(hdrTextureCube_);
}

MaterialCubeMap::~MaterialCubeMap() {}

Shader* MaterialCubeMap::Bind() {
	Material::Bind();

	glDisable(GL_DEPTH_TEST);
	return shader;
}

void MaterialCubeMap::UnBind() {
	Material::UnBind();
}
