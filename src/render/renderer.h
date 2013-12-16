#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <ctime>
#include <stdexcept>

#include "graphics.h"
#include "globals.h"

#include "mesh.h"
#include "shader.h"
#include "camera.h"
#include "shaderlibrary.h"
#include "cubemap.h"
#include "objparser.h"
#include "framebuffer.h"
#include "texture.h"

using namespace std;

#define MAX_DOWNSCALE_FBO 4

class Renderer {
    public:
        Renderer(int width, int height, Camera* camera);
        ~Renderer();

        void Render(float time);
        void Init();
    private:
        void SwapBuffers();
        void SendDefaultUniforms();
        void RenderCubeMap();
        void LoadShaders();
        void LoadMeshes();
        void BloomPass(float time);
        void BrightPass(float threshold);
        void CubicLensPass();
        void LensFlarePass();
        void ToneMap(float time);
        void Capture();
        void DrawMesh(Mesh* mesh, bool sendDefaultUniforms = true);
        void SetFiltering(GLint filtering);
        int width, height;

        Camera* camera;
        ShaderLibrary* shaderLibrary;
        CubeMap* cubemap;
        Mesh* model;
        Mesh* quad;

        Shader* _shader;
        Framebuffer* mainFBO;
        Framebuffer* readFBO;
        Framebuffer* writeFBO;
        Framebuffer* downScaleFBO[MAX_DOWNSCALE_FBO];
};

#endif
