#include "app.h"
#include "glfwfunc.h"

App::App(int width_, int height_, bool fullscreen_) : width(width_), height(height_), fullscreen(fullscreen_) {}

App::~App() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void App::MainLoop() {
    double lastTime = glfwGetTime();
    int frames = 0;
    int cpt = 0;
    float avgFps = 0;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        double time = glfwGetTime();

        /* update inputs */
        Update(time - lastTime);

        if(frames * 4 < MAX_FPS) {
            /* render scene in buffer */
            renderer->Render(time);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* update frame number */
            frames++;
        }

        /* Poll for and process events */
        glfwPollEvents();

        float lastMod = fmodf(lastTime, 0.25f);
        float mod = fmodf(time, 0.25f);
        
        if(mod < lastMod) {
            cout << "FPS: " << frames * 4 << "\r";
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

    // fix a bug that made the cursor out of screen for the first time
    if(!fullscreen) {
        if(abs(cursorX) <= 100 && abs(cursorY) <= 100) {
            camera.Rotate(glm::vec2(mouseSensitivity * cursorY, mouseSensitivity * cursorX));
        }
    } else {
        // fixing a glfw issue on cursor position, in fullscreen it's not sending the delta position of the mouse
        static glm::vec2 lastCursorPos = glm::vec2(0,0); 
        camera.Rotate(glm::vec2(mouseSensitivity * (cursorY - lastCursorPos.y), mouseSensitivity * (cursorX - lastCursorPos.x)));
        lastCursorPos.x = cursorX;
        lastCursorPos.y = cursorY;
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

    DisplayGraphicInfo();

    camera.SetAspectRatio(width / height);
    //camera.SetFov(100);

	renderer = new Renderer(width, height, &camera);

    //currentEnvIndex = 0;
    //renderer->NextEnv("rnl_cross");
	renderer->Init();
}
