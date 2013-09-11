#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>

#include "graphics.h"

using namespace std;

class Mesh {
public:
	Mesh(void);
	Mesh(vector<glm::vec3>& vertices, std::vector<glm::vec2>& uvs);
	~Mesh(void);

	virtual void Draw();
	static Mesh* Triangle();

	void SetTexture(GLuint texture);
	GLuint GetTexture();
private:
	void CreateBufferData();

	GLuint texture;
	GLuint vao;
	GLuint vbo[BUFFER_COUNT];
	GLuint type;

	unsigned int numVertices;

	glm::vec3* vertices;
	glm::vec4* colours;
	glm::vec2* texCoords;
};

#endif