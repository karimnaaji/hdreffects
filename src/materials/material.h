#ifndef MATERIAL_H
#define MATERIAL_H

#include "shader.h"
#include <vector>

class Material {
	public:
		Material(Shader* shader_);
		virtual ~Material();

		virtual Shader* Bind();
		virtual void UnBind();
        void AddTexture(Texture* texture);
	protected:
		Shader* shader;	
    private:
        vector<Texture*> textures;
};

#endif
