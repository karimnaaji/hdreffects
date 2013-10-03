#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "mesh.h"
#include "geometries.h"
#include "materialcubemap.h"

class CubeMap : public Mesh {
    public:
        CubeMap(MaterialCubeMap* material_);
        ~CubeMap();
};

#endif
