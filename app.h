#ifndef APP_H
#define APP_H

#include <stdexcept>

#include "graphics.h"
#include "camera.h"
#include "renderer.h"

using namespace std;

class App {
public:
	App(int width_, int height_);
	~App();

	void DisplayGraphicInfo();
	void MainLoop();
	void Init();
	void Update(float elapsedTime);

private:
	void InitGLFW();

	unsigned int width, height;
	GLuint fbo;

	GLFWwindow* window;
	Renderer* renderer;
	Camera camera;
};

#endif