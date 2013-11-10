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
        void SetColour(glm::vec4& colour);
	protected:
		Shader* shader;	
        glm::vec4 materialColour;
    private:
        vector<Texture*> textures;
};

#endif
