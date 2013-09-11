#ifndef APP_H
#define APP_H

#include <stdexcept>

#include "graphics.h"
#include "renderer.h"

using namespace std;

class App {
public:
	App(int width_, int height_);
	~App(void);

	void DisplayGraphicInfo();
	void MainLoop();
	void Init();

private:
	void InitGLFW();

	unsigned int width, height;
	GLuint fbo;

	GLFWwindow* window;
	Renderer* renderer;
};

#endif