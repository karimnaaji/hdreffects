#include "materialcubemap.h"

MaterialCubeMap::MaterialCubeMap(Shader* shader, HDRCubeMap* cubeMap_) : Material(shader), cubeMap(cubeMap_) {
	//cubeMap->Load();	
}

MaterialCubeMap::~MaterialCubeMap() {}

Shader* MaterialCubeMap::Bind() {
	return Material::Bind();
}

void MaterialCubeMap::UnBind() {
	Material::UnBind();
}
