#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"

class Material {
	public:
		Material(Shader* shader_);
		~Material();

	private:
		Shader* shader;	
};

#endif