#ifndef APP_H
#define APP_H

#include <stdexcept>

#include "graphics.h"
#include "camera.h"
#include "renderer.h"

using namespace std;

#define MAX_FPS 60

class App {
public:
	App(int width, int height, bool fullscreen);
	~App();

	void DisplayGraphicInfo();
	void MainLoop();
	void Init();
	void Update(float elapsedTime);

private:
	void InitGLFW();

	unsigned int width, height;
	bool fullscreen;
	GLuint fbo;

	GLFWwindow* window;
	Renderer* renderer;
	Camera camera;
    vector<string> environments;
    int currentEnvIndex;
};

#endif

