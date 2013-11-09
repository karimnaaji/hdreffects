#include "objparser.h"

Geometry* ObjParser::Parse(string filename) {
    string path = string(OBJ_RELATIVE_PATH) + filename + string(OBJ_EXT);
    std::ifstream f(path.c_str(), ios::in);

    if(!f) {
        return NULL;
    }

    string token;
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    vector<s_face> faces;

    while(!f.eof()) {
        f >> token; 

        if(token == "#") {
            f.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        } else if(token == "v") {   // vertex
            glm::vec3 vertex;
            f >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if(token == "vt") {  // tex coord
            glm::vec2 uv;
            f >> uv.x >> uv.y;
            uvs.push_back(uv);
        } else if(token == "vn") {  // vertex normal
            glm::vec3 normal;
            f >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        } else if(token == "f") {   // face
            string faceLine;
            bool noTexIndices = false;
            getline(f, faceLine);

            if(faceLine.find("//") != string::npos) {
                noTexIndices = true;
            }

            for(int i = 0; i < faceLine.length(); ++i) {
                if(faceLine[i] == '/') {
                    faceLine[i] = ' ';
                }
            }

            stringstream ss(faceLine);
            string indexToken;
            s_face face;
            for(int i = 0; i < 3; ++i) {
                ss >> face.vertexIndex[i];
                ss >> face.normalIndex[i];
            }
            faces.push_back(face);
        }
    }

    unsigned int* indices = new unsigned int[faces.size()*3];
    for(int i = 0; i < faces.size(); ++i) {
        indices[i*3+0] = faces[i].vertexIndex[0];
        indices[i*3+1] = faces[i].vertexIndex[1];
        indices[i*3+2] = faces[i].vertexIndex[2];
    }
    Geometry* geometry = new Geometry(reinterpret_cast<glm::vec3*>(&vertices[0]), indices, vertices.size(), faces.size()*3);
    delete[] indices;

    f.close();
    return geometry;
}
