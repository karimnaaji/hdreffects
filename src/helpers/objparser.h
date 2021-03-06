#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip> 

#include "graphics.h"
#include "mesh.h"

class ObjParser {
    public:
        static Geometry* Parse(string filename);
};

#endif
