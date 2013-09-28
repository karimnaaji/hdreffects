#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "graphics.h"

enum PrimitiveType { TRIANGLE = GL_TRIANGLES };

class Geometry {
	public:
		Geometry();
		Geometry(glm::vec3* vertices, glm::vec4* colours, int verticesCount);
		~Geometry();

		glm::vec3* GetVertices();
		glm::vec2* GetUVs();
		glm::vec4* GetColours();
		
		int GetVerticesCount(); 
		int GetUVsCount();
		PrimitiveType GetType();

		static Geometry* Triangle();

		bool HasColors();
		bool HasTexCoords();

	private:
		glm::vec3* vertices;
		glm::vec2* uvs;
		glm::vec4* colours;

		int verticesCount;
		int uvsCount;

		PrimitiveType primitiveType;
};

#endif