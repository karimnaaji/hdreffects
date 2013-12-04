#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <ctime>
#include <stdexcept>

#include "graphics.h"

#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "shaderlibrary.h"
#include "cubemap.h"
#include "objparser.h"
#include "framebuffer.h"
#include "texture.h"

using namespace std;

class Renderer {
    public:
        Renderer(int width, int height, Camera* camera);
        ~Renderer();

        void Render();
        void Init();
    private:
        void SwapBuffers();
        void SendDefaultUniforms();
        void RenderCubeMap();
        void LoadShaders();
        void LoadMeshes();
        void DrawMesh(Mesh* mesh, bool sendDefaultUniforms = true);
        int width, height;

        Camera* camera;
        ShaderLibrary* shaderLibrary;
        CubeMap* cubemap;
        Mesh* model;
        Mesh* quad;

        Shader* _shader;
        Framebuffer* readFBO;
        Framebuffer* writeFBO;
};

#endif
