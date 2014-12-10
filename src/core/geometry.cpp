#include "geometry.h"

Geometry::Geometry(glm::vec3* vertices_, unsigned int* indices_, int verticesCount_, int indicesCount_) {
    isInterleaved = false;
    uvs = NULL;
    colours = NULL;
    normals = NULL;
    indices = new unsigned int[indicesCount_]();
    vertices = new glm::vec3[verticesCount_]();

    memcpy(vertices, vertices_, verticesCount_ * sizeof(glm::vec3));
    memcpy(indices, indices_, indicesCount_ * sizeof(unsigned int));

    verticesCount = verticesCount_;
    indicesCount = indicesCount_;

    primitiveType = TRIANGLE;
}

Geometry::Geometry(glm::vec3* verticesInterleaved_, int verticesCount_) {
    isInterleaved = true;
    uvs = NULL;
    colours = NULL;
    normals = NULL;
    indices = NULL;
    vertices = new glm::vec3[verticesCount_]();

    memcpy(vertices, verticesInterleaved_, verticesCount_ * sizeof(glm::vec3));

    verticesCount = verticesCount_;
    indicesCount = 0;

    primitiveType = TRIANGLE;
}

Geometry::~Geometry() {
    delete[] vertices;
    delete[] uvs;
    delete[] colours;
    delete[] indices;
    delete[] normals;
}

void Geometry::SetColours(glm::vec4* colours_) {
    if(IsInterleaved()) {
        cerr << "Wrong usage of interleaved geometry" << endl;
        return;
    }

    if(colours != NULL)
        delete[] colours;

    colours = new glm::vec4[verticesCount];
    memcpy(colours, colours_, verticesCount * sizeof(glm::vec4));
}

void Geometry::SetUVs(glm::vec2* uvs_) {
    if(IsInterleaved()) {
        cerr << "Wrong usage of interleaved geometry" << endl;
        return;
    }

    if(uvs != NULL)
        delete[] uvs;

    uvs = new glm::vec2[verticesCount];
    memcpy(uvs, uvs_, verticesCount * sizeof(glm::vec2));
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

bool Geometry::HasNormals() {
    return normals != NULL;
}

int Geometry::GetVerticesCount() {
    return verticesCount;
}

int Geometry::GetIndicesCount() {
    return indicesCount;
}

int Geometry::GetTexCoordCount() {
    if(HasTexCoords() && primitiveType == TRIANGLE) {
        return GetVerticesCount()/3 * 2;
    } // TODO: compute other cases
    return 0;
}

unsigned int* Geometry::GetIndices() {
    return indices;
}

glm::vec3* Geometry::GetVertices() {
    return vertices;
}

glm::vec3* Geometry::GetNormals() {
    return normals;
}

glm::vec2* Geometry::GetUVs() {
    return uvs;
}

glm::vec4* Geometry::GetColours() {
    return colours;
}

bool Geometry::IsInterleaved() {
    return isInterleaved;
}
