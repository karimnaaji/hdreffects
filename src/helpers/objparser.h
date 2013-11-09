#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "graphics.h"
#include "mesh.h"

class ObjParser {
    public:
        ObjParser();
        ~ObjParser();

        static Geometry* Parse(string filename);
};

typedef struct s_face {
    unsigned int vertexIndex[3];
    unsigned int uvIndex[3];
    unsigned int normalIndex[3];
} s_face;

#endif
