#include "materialcubemap.h"

MaterialCubeMap::MaterialCubeMap(Shader* shader, HDRTextureCube* hdrTextureCube_) : Material(shader), hdrTextureCube(hdrTextureCube_) {}

MaterialCubeMap::~MaterialCubeMap() {}

Shader* MaterialCubeMap::Bind() {
	Material::Bind();

	hdrTextureCube->Bind();
	shader->SendUniform("cubeMap", hdrTextureCube);

	return shader;
}

void MaterialCubeMap::UnBind() {
	Material::UnBind();
}
