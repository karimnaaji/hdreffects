#ifndef MATERIAL_CUBE_MAP_H
#define MATERIAL_CUBE_MAP_H

#include "material.h"
#include "hdrcubemap.h"

class MaterialCubeMap : Material {
	public:
		MaterialCubeMap(Shader* shader, HDRCubeMap* cubeMap);
		~MaterialCubeMap();

		Shader* Bind();
		void UnBind();
	private:
		 HDRCubeMap* cubeMap;
};

#endif
