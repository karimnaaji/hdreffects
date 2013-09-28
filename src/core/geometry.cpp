#include "geometry.h"

Geometry::Geometry() {
	uvs = NULL;
	vertices = NULL;
	colours = NULL;

	verticesCount = 0;
	uvsCount = 0;

	primitiveType = TRIANGLE;
}

Geometry::Geometry(glm::vec3* vertices_, glm::vec4* colours_, int verticesCount_) {
	uvs = NULL;
	vertices = vertices_;
	colours = colours_;

	verticesCount = verticesCount_;
	uvsCount = 0;

	primitiveType = TRIANGLE;
}

Geometry::~Geometry() {
	delete[] vertices;
	delete[] uvs;
	delete[] colours;
}

PrimitiveType Geometry::GetType() {
	return primitiveType;
}

bool Geometry::HasColors() {
	return colours != NULL;
}

bool Geometry::HasTexCoords() {
	return uvs != NULL;
}

int Geometry::GetVerticesCount() {
	return verticesCount;
}

int Geometry::GetUVsCount() {
	return uvsCount;
}

glm::vec3* Geometry::GetVertices() {
	return vertices;
}

glm::vec2* Geometry::GetUVs() {
	return uvs;
}

glm::vec4* Geometry::GetColours() {
	return colours;
}