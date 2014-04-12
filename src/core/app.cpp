#include "app.h"
#include "glfwfunc.h"

App::App(int width_, int height_, bool fullscreen_) : width(width_), height(height_), fullscreen(fullscreen_) {}

App::~App() {
	delete renderer;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::MainLoop() {
    double lastTime = glfwGetTime();
    int frames = 0;
    int cpt = 0;
    float avgFps = 0;
    
    while (!glfwWindowShouldClose(window)) {
        double time = glfwGetTime();

        Update(time - lastTime);

        if(frames * 4 < MAX_FPS) {
            renderer->Render(time);

            glfwSwapBuffers(window);

            frames++;
        }

        glfwPollEvents();

        float lastMod = fmodf(lastTime, 0.25f);
        float mod = fmodf(time, 0.25f);
        
        if(mod < lastMod) {
            Debug::Instance() << "FPS: " << frames * 4 << "\r";
            avgFps += frames * 4;
            cout.flush();
            frames = 0;
            cpt++;
        }

        lastTime = time;
    }

    cout << "Average FPS: " << avgFps / cpt << endl;
}

void App::Update(float elapsedTime) {

    if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(window, true);

    const float moveSpeed = 2.0f;

    if(glfwGetKey(window, 'N')) {
        //renderer->NextEnv(environments[(++currentEnvIndex) % environments.size()]);
    }

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

    const float mouseSensitivity = 0.1f;
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);

// fix a bug that made the cursor out of screen for the first time (only apple build)
#ifdef __APPLE__
    if(!fullscreen) {
#endif
        if(abs(cursorX) <= 100 && abs(cursorY) <= 100) {
            camera.Rotate(glm::vec2(mouseSensitivity * cursorY, mouseSensitivity * cursorX));
        }
#ifdef __APPLE__
    } else {
        // fixing a glfw issue on cursor position, in fullscreen it's not sending the delta position of the mouse
        static glm::vec2 lastCursorPos = glm::vec2(0,0); 
        camera.Rotate(glm::vec2(mouseSensitivity * (cursorY - lastCursorPos.y), mouseSensitivity * (cursorX - lastCursorPos.x)));
        lastCursorPos.x = cursorX;
        lastCursorPos.y = cursorY;
    }
#endif

    glfwSetCursorPos(window, 0, 0); 
}

void App::DisplayGraphicInfo() {
    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "Vendor : " << glGetString(GL_VENDOR) << endl;
    cout << "GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
    cout << "Renderer : " << glGetString(GL_RENDERER) << endl;
}

void App::InitGLFW() {
    if (!glfwInit())
        throw std::runtime_error("glfwInit failed");

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    string appName = "HDR Image Based Lighting";

    if(fullscreen)
        window = glfwCreateWindow(width, height, appName.c_str(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(width, height, appName.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("glfwOpenWindow failed.");
    }

    glfwSetCursorPos(window, 0, 0);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetKeyCallback(window, KeyCallback);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("glewInit failed.");
    }
}

void App::Init() {
	InitGLFW();

    DisplayGraphicInfo();

    camera.SetAspectRatio(width / height);

	renderer = new Renderer(width, height, &camera);
	renderer->Init();
}
