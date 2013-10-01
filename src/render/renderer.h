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

using namespace std;

class Renderer {
public:
	Renderer(int width, int height, Camera* camera);
	~Renderer();

	void Render();
	void Init();
private:
	void LoadShaders();
	void CreateFrameBuffer(GLuint renderTexture);
	GLuint CreateTexture(int width, int height, bool isDepth = false);

	Mesh* triangle;
	Mesh* quad;

	Material* _material;
	Shader* _shader;

	GLuint fbo;
	GLuint renderTexture;
	Camera* camera;
	ShaderLibrary* shaderLibrary;
};

#endif
