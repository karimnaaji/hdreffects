#include "app.h"

App::App(int width_, int height_, bool fullscreen_) : width(width_), height(height_), fullscreen(fullscreen_) {}

App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::MainLoop() {
    double lastTime = glfwGetTime();
    int frames = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        double time = glfwGetTime();

        /* update inputs */
        Update(time - lastTime);

        /* render scene in buffer */
        renderer->Render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* update frame number */
        frames++;

        /* Poll for and process events */
        glfwPollEvents();

        float lastMod = fmodf(lastTime, 1.0f);
        float mod = fmodf(time, 1.0f);
        
        if(mod < lastMod) {
            cout << "FPS: " << frames << endl;
            frames = 0;
        }

        lastTime = time;
    }
}

void App::Update(float elapsedTime) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    const float moveSpeed = 2.0f;

    if(glfwGetKey(window, 'S')) {
        camera.Translate(elapsedTime * moveSpeed * -camera.Forward());
    } else if(glfwGetKey(window, 'W')) {
        camera.Translate(elapsedTime * moveSpeed * camera.Forward());
    }

    if(glfwGetKey(window, 'A')) {
        camera.Translate(elapsedTime * moveSpeed * -camera.Right());
    } else if(glfwGetKey(window, 'D')) {
        camera.Translate(elapsedTime * moveSpeed * camera.Right());
    }

    const float mouseSensitivity = 0.05f;
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);

    // fix a bug that made the cursor out of screen for the first time
    if(abs(cursorX) <= 100 && abs(cursorY) <= 100)
        camera.Rotate(glm::vec2(mouseSensitivity * cursorY, mouseSensitivity * cursorX));

    if(cursorX != 0 || cursorY != 0) {
        cout << "Mouse pos : " << cursorX << ";" << cursorY << endl;
    }

    glfwSetCursorPos(window, 0, 0); 
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

    if(fullscreen)
        window = glfwCreateWindow(width, height, "Hello World", glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("glfwOpenWindow failed.");
    }

    glfwSetCursorPos(window, 0, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("glewInit failed.");
    }
}

void App::Init() {
	InitGLFW();

    camera.SetAspectRatio(width / height);

	renderer = new Renderer(width, height, &camera);

	renderer->Init();
}