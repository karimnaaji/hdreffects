#include "cubemap.h"

CubeMap::CubeMap(MaterialCubeMap* material_) : Mesh() {
    geometry = Geometries::Cube(1.0f);
    material = material_;
}

CubeMap::~CubeMap() {}