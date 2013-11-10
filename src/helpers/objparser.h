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

#endif
