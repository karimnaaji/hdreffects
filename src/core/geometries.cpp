#include "geometries.h"

Geometry* Geometries::Cube(float size) {
    float vertices[] = {
        -size,  size,  size,
        -size, -size,  size,
        size, -size,  size,
        size,  size,  size,
        -size,  size, -size,
        -size, -size, -size,
        size, -size, -size,
        size,  size, -size,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        3, 2, 6,
        3, 6, 7,
        0, 4, 7,
        0, 7, 3,
        4, 6, 7,
        4, 6, 5,
        0, 5, 4,
        0, 5, 1,
        1, 6, 5,
        1, 6, 2,
    };

    Geometry* geometry = new Geometry(reinterpret_cast<glm::vec3*>(vertices), indices, 8, 36);
    return geometry;
}

Geometry* Geometries::Quad(float size) {
    float vertices[] = {
        -size,  size, 0.0f,
        -size, -size, 0.0f,
        size, -size, 0.0f,
        size,  size, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    float uvs[] = {
        0, 1,
        0, 0,
        1, 0,
        1, 1,
    };

    Geometry* quad = new Geometry(reinterpret_cast<glm::vec3*>(vertices), indices, 4, 6);
    quad->SetUVs(reinterpret_cast<glm::vec2*>(uvs));

    return quad;
}
