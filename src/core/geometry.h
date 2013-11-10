#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include "graphics.h"

enum PrimitiveType { 
	TRIANGLE = GL_TRIANGLES, 
	QUADS = GL_QUADS, 
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
};

class Geometry {
	public:
        Geometry(glm::vec3* vertices, unsigned int* indices, int verticesCount, int indicesCount);
        Geometry(glm::vec3* interleavedVertices, int verticesCount);
		~Geometry();

		glm::vec3* GetVertices();
		glm::vec2* GetUVs();
		glm::vec4* GetColours();
        glm::vec3* GetNormals();
        unsigned int* GetIndices();
		
		int GetVerticesCount(); 
        int GetIndicesCount();
        int GetTexCoordCount();

		PrimitiveType GetType();
        void SetPrimitive(PrimitiveType primitiveType);

        void SetColours(glm::vec4* colours);
        void SetUVs(glm::vec2* uvs);

		static Geometry* Triangle();

		bool HasColors();
		bool HasTexCoords();
        bool HasIndices();
        bool HasNormals();
        bool IsInterleaved();
	private:
        bool isInterleaved;
		glm::vec3* vertices;
		glm::vec2* uvs;
        glm::vec3* normals;
		glm::vec4* colours;
        unsigned int* indices;

        int indicesCount;
		int verticesCount;

		PrimitiveType primitiveType;
};

#endif
