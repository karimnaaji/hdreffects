#include "objparser.h"

Geometry* ObjParser::Parse(string filename) {
    string path = string(OBJ_RELATIVE_PATH) + filename + string(OBJ_EXT);

    ifstream file(path.c_str(), ios::in); 
    if(!file) {
        cerr << "Can't open file " << path << endl;
        return NULL;
    }

    int lines = 0; 
    while(file.ignore(std::numeric_limits<int>::max(), '\n')) { 
        ++lines; 
    } 
    file.close();

    ifstream f(path.c_str(), ios::in);

    cout << "Loading " << path << ".. " << endl;

    string token;
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;
    vector<glm::vec3> interleavedArray;
    int currentLine = 0;

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
                        interleavedArray.push_back(vertices[atoi(faceToken.c_str()) - 1]);
                    } else {
                        interleavedArray.push_back(normals[atoi(faceToken.c_str()) - 1]);
                    }
                }
            }
        }
        currentLine++;

        float ratio = currentLine/(float)lines;
        int barWidth = 50;
        cout << "[";
        int pos = barWidth * ratio;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) cout << "=";
            else if (i == pos) cout << ">";
            else cout << " ";
        }
        cout << "] " << int(ratio * 100.0) << " %\r";
        cout.flush();
    }
    f.close();

    cout << endl;

    cout << "Loaded model :" << endl;
    cout << " - " << interleavedArray.size() / 2 << " vertices" << endl;

    Geometry* geometry = new Geometry(reinterpret_cast<glm::vec3*>(&interleavedArray[0]), interleavedArray.size());

    return geometry;
}
