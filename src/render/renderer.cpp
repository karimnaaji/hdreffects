#include "renderer.h"

Renderer::Renderer(int width, int height, Camera* camera_) {
	shaderLibrary = new ShaderLibrary();
	LoadShaders();

    camera = camera_;
    triangle = Mesh::Triangle(shaderLibrary);

	_material = NULL;
	_shader = NULL;
}

Renderer::~Renderer() {
	delete shaderLibrary;
  	delete triangle;
	delete shaderLibrary;
}

void Renderer::LoadShaders() {
	shaderLibrary->AddShader(string("basic"));
}

void Renderer::Init() {
    glClearColor(0.1, 0.1, 0.2, 1.0);
	
	LoadShaders();
}

void Renderer::Render() {
    float time = (float) clock() / (CLOCKS_PER_SEC / 1000);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	_material = triangle->GetMaterial();
	_shader = _material->Bind();

    glUniform1f(glGetUniformLocation(_shader->Program(), "globalTime"), time);
    glUniformMatrix4fv(glGetUniformLocation(_shader->Program(), "view"), 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));

    triangle->Draw();

	_material->UnBind();
}

void Renderer::CreateFrameBuffer(GLuint renderTexture) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // attach the render texture to the frame buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Renderer::CreateTexture(int width, int height, bool isDepth) {
    GLuint textureId;

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    GLenum internalFormat = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA8;
    GLenum format = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_FLOAT, NULL);                

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}
