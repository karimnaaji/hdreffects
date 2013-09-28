#ifndef MESH_H
#define MESH_H

#include <vector>
#include <iostream>

#include "graphics.h"
#include "mesh.h"
#include "material.h"
#include "geometry.h"

using namespace std;

class Mesh {
public:
	Mesh(Geometry *geometry, Material* material);
	~Mesh(void);

	void Draw();
	static Mesh* Triangle();

	void SetTexture(GLuint texture);
	GLuint GetTexture();
	Geometry* GetGeometry();
private:
	void CreateBufferData();

	GLuint texture;
	GLuint vao;
	GLuint vbo[BUFFER_COUNT];

	Material *material;
	Geometry *geometry;
};

#endif