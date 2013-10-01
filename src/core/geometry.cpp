#include "geometry.h"

Geometry::Geometry() {
	uvs = NULL;
	vertices = NULL;
	colours = NULL;
    indices = NULL;

	verticesCount = 0;
	uvsCount = 0;
    indicesCount = 0;

	primitiveType = TRIANGLE;
}

Geometry::Geometry(glm::vec3* vertices_, unsigned int* indices_, int verticesCount_, int indicesCount_) {
    uvs = NULL;
    indices = new unsigned int[indicesCount_]();
    vertices = new glm::vec3[verticesCount_]();
    colours = NULL;

    memcpy(vertices, vertices_, verticesCount_ * sizeof(glm::vec3));
    memcpy(indices, indices_, indicesCount_ * sizeof(unsigned int));

    verticesCount = verticesCount_;
    uvsCount = 0;
    indicesCount = indicesCount_;

    primitiveType = TRIANGLE;
}

Geometry::Geometry(glm::vec3* vertices_, glm::vec4* colours_, int verticesCount_) {
	uvs = NULL;
    indices = NULL;
    vertices = new glm::vec3[verticesCount_];
	colours = new glm::vec4[verticesCount_];

    memcpy(vertices, vertices_, verticesCount_ * sizeof(glm::vec3));   
    memcpy(colours, colours_, verticesCount_ * sizeof(glm::vec4));

	verticesCount = verticesCount_;
	uvsCount = 0;
    indicesCount = 0;

	primitiveType = TRIANGLE;
}

Geometry::~Geometry() {
	delete[] vertices;
	delete[] uvs;
	delete[] colours;
    delete[] indices;
}

void Geometry::SetColours(glm::vec4* colours_) {
    colours = colours_;
}

void Geometry::SetUVs(glm::vec2* uvs_) {
    if(uvs != NULL)
        delete[] uvs;

    uvs = new glm::vec2[verticesCount];
    //memcpy(uvs, uvs_, verticesCount * sizeof(glm::vec2));
}

void Geometry::SetPrimitive(PrimitiveType primitiveType_) {
    primitiveType = primitiveType_;
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

bool Geometry::HasIndices() {
  return indices != NULL;
}

int Geometry::GetVerticesCount() {
	return verticesCount;
}

int Geometry::GetUVsCount() {
	return uvsCount;
}

int Geometry::GetIndicesCount() {
    return indicesCount;
}

unsigned int* Geometry::GetIndices() {
    return indices;
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
