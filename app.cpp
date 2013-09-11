#include "app.h"

App::App(int width_, int height_) : width(width_), height(height_) {}

App::~App(void) {
	delete renderer;

    glfwTerminate();
}

void App::MainLoop() {
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        renderer->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

void App::DisplayGraphicInfo() {
    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "Vendor : " << glGetString(GL_VENDOR) << endl;
    cout << "GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "Renderer : " << glGetString(GL_RENDERER) << endl;
}


void App::InitGLFW() {
    /* Initialize the library */
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("glfwOpenWindow failed.");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw std::runtime_error("glewInit failed.");
    }
}

void App::Init() {
	InitGLFW();
	
	renderer = new Renderer();
	renderer->Init();
}