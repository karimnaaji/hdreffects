#include "materialcubemap.h"

MaterialCubeMap::MaterialCubeMap(Shader* shader, HDRTextureCube* hdrTextureCube_) : Material(shader), hdrTextureCube(hdrTextureCube_) {}

MaterialCubeMap::~MaterialCubeMap() {}

Shader* MaterialCubeMap::Bind() {
	Material::Bind();

	glDisable(GL_DEPTH_TEST);

	hdrTextureCube->Bind();
	shader->SendUniform(hdrTextureCube->GetName(), hdrTextureCube);

	return shader;
}

void MaterialCubeMap::UnBind() {
	Material::UnBind();
}
