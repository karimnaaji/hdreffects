#include "objparser.h"

Geometry* ObjParser::Parse(string filename) {
    string path = string(OBJ_RELATIVE_PATH) + filename + string(OBJ_EXT);
    std::ifstream f(path.c_str(), ios::in);

    if(!f) {
        cerr << "Can't open file " << path << endl;
        return NULL;
    }

    cout << "Loading " << path << endl;

    string token;
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec3> normalsContiguous;
    vector<glm::vec2> uvs;
    vector<unsigned int> vertexIndices;
    vector<unsigned int> normalIndices;

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
            string faceToken;
            for(int i = 0; i < 6; ++i) {
                ss >> faceToken;
                if(faceToken.find_first_not_of("\t\n ") != string::npos) {
                    if(i % 2 == 0) {
                        vertexIndices.push_back(atoi(faceToken.c_str()) - 1);
                    } else {
                        normalIndices.push_back(atoi(faceToken.c_str()) - 1);
                    }
                }
            }
        }
    }
    f.close();

    for(int i = 0; i < normalIndices.size(); ++i) {
        normalsContiguous.push_back(normals[normalIndices[i]]);
    }

    Geometry* geometry = new Geometry(reinterpret_cast<glm::vec3*>(&vertices[0]), 
            reinterpret_cast<unsigned int*>(&vertexIndices[0]), 
            reinterpret_cast<glm::vec3*>(&normalsContiguous[0]), 
            vertices.size(), vertexIndices.size());

    return geometry;
}
