#ifndef MATERIAL_CUBE_MAP_H
#define MATERIAL_CUBE_MAP_H

#include "material.h"
#include "hdrtexturecube.h"

class MaterialCubeMap : public Material {
	public:
		MaterialCubeMap(Shader* shader, HDRTextureCube* hdrTextureCube);
		~MaterialCubeMap();

		Shader* Bind();
		void UnBind();
	private:
		 HDRTextureCube* hdrTextureCube;
};

#endif
