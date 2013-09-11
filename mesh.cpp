#include "mesh.h"

Mesh::Mesh(void) {
	vertices = NULL;
	colours = NULL;
	texCoords = NULL;
	texture = 0;
	numVertices = 0;
	type = GL_TRIANGLES;

	for(int i = 0; i < BUFFER_COUNT; ++i) {
		vbo[i] = 0;
	}
	
	glGenVertexArrays(1, &vao);
}

Mesh::Mesh(vector<glm::vec3>& verticesList, std::vector<glm::vec2>& uvs) {
	numVertices = verticesList.size();
	vertices = new glm::vec3[numVertices];
	texCoords = new glm::vec2[numVertices];
	colours = NULL;
	texture = 0;
	type = GL_TRIANGLES;

	vector<glm::vec3>::iterator it1;
	int i = 0;
	for(it1 = verticesList.begin(); it1 != verticesList.end(); ++it1, ++i) {
		vertices[i] = *it1;
	}

	vector<glm::vec2>::iterator it2;
	i = 0;
	for(it2 = uvs.begin(); it2 != uvs.end(); ++it2, ++i) {
		texCoords[i] = *it2;
	}

	for(int i = 0; i < BUFFER_COUNT; ++i) {
		vbo[i] = 0;
	}
	
	glGenVertexArrays(1, &vao);
	CreateBufferData();
}

Mesh::~Mesh(void) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(BUFFER_COUNT, vbo);

	delete[] texCoords;
	delete[] vertices;
	delete[] colours;
}

void Mesh::SetTexture(GLuint tex) {
	texture = tex;
}

void Mesh::Draw() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(vao);
	glDrawArrays(type, 0, numVertices);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Mesh* Mesh::Triangle() {
	Mesh *mesh = new Mesh();

	mesh->numVertices = 3;

	mesh->vertices = new glm::vec3[mesh->numVertices];
	mesh->vertices[0] = glm::vec3(0, 1, 0);
	mesh->vertices[1] = glm::vec3(-1, -1, 0);
	mesh->vertices[2] = glm::vec3(1, -1, 0);

	mesh->colours = new glm::vec4[mesh->numVertices];
	mesh->colours[0] = glm::vec4(1, 0, 0, 1);
	mesh->colours[1] = glm::vec4(0, 1, 0, 1);
	mesh->colours[2] = glm::vec4(0, 0, 1, 1);

	mesh->CreateBufferData();

	return mesh;
}

void Mesh::CreateBufferData() {
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo[VERTEX_BUFFER]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);

	// send data to opengl
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX_BUFFER);

	if(texCoords) {
		glGenBuffers(1, &vbo[TEXTURE_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[TEXTURE_BUFFER]);

		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), texCoords, GL_STATIC_DRAW);

		glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(TEXTURE_BUFFER);
	}
	if(colours) {
		glGenBuffers(1, &vbo[COLOUR_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[COLOUR_BUFFER]);

		glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec4), colours, GL_STATIC_DRAW);

		glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(COLOUR_BUFFER);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}