#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <ctime>

#include "graphics.h"
#include "mesh.h"
#include "shader.h"

using namespace std;

class Renderer {
public:
	Renderer(void);
	~Renderer(void);

	void Render();
	void Init();
private:
	void CreateFrameBuffer(GLuint renderTexture);
	GLuint CreateTexture(int width, int height, bool isDepth = false);

	Mesh *triangle;
	Mesh *quad;
	Shader *shader;
	Shader *rgbShiftShader;
	GLuint fbo;
	GLuint renderTexture;
};

#endif