#include "renderer.h"

Renderer::Renderer() {
    triangle = Mesh::Triangle();

	  vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;

	  vertices.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
    uvs.push_back(glm::vec2(0, 0));
   	vertices.push_back(glm::vec3( 1.0f, -1.0f, 0.0f));
    uvs.push_back(glm::vec2(1, 0));
    vertices.push_back(glm::vec3(-1.0f,  1.0f, 0.0f));
    uvs.push_back(glm::vec2(0, 1));

    vertices.push_back(glm::vec3(-1.0f,  1.0f, 0.0f));
    uvs.push_back(glm::vec2(0, 1));
   	vertices.push_back(glm::vec3( 1.0f, -1.0f, 0.0f));
    uvs.push_back(glm::vec2(1, 0));
   	vertices.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
    uvs.push_back(glm::vec2(1, 1));

    quad = new Mesh(vertices, uvs);

    string vertex = "basic.vert";
    string fragment = "basic.frag";
    string rgbShift = "rgbshift.frag";
    
    shader = new Shader(vertex, fragment);
    rgbShiftShader = new Shader(vertex, rgbShift);
}

Renderer::~Renderer() {
	delete shader;
  delete rgbShiftShader;
	delete triangle;
  delete quad;

  glDeleteTextures(1, &renderTexture);
  glDeleteFramebuffers(1, &fbo);
  glUseProgram(0);
}

void Renderer::Init() {
    glClearColor(0.1, 0.1, 0.2, 1.0);

    shader->Link();
    rgbShiftShader->Link();

    renderTexture = CreateTexture(640, 480);
    CreateFrameBuffer(renderTexture);

    quad->SetTexture(renderTexture);
}

void Renderer::Render() {
    float time = (float) clock() / (CLOCKS_PER_SEC / 1000);

    // first pass into frame buffer
    glUseProgram(shader->Program());
  	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUniform1i(glGetUniformLocation(shader->Program(), "frameTexture"), 0);
    triangle->Draw();
  	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glUseProgram(0);

    // second pass
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(rgbShiftShader->Program());
    // sample texture from texture unit 0
    glUniform1i(glGetUniformLocation(rgbShiftShader->Program(), "frameTexture"), 0);
    glUniform1f(glGetUniformLocation(rgbShiftShader->Program(), "globalTime"), time);
  	quad->Draw();
    glUseProgram(0);
}

void Renderer::CreateFrameBuffer(GLuint renderTexture) {
  glGenFramebuffers(1, &fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);

  // once the frame is binded, then you don't render to the screen but to whatever
  // is attached to this frame buffer

  // attach the render texture to the frame buffer
  glFramebufferTexture(
    GL_FRAMEBUFFER,      
    GL_COLOR_ATTACHMENT0,
    renderTexture, 
    0
    );

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Renderer::CreateTexture(int width, int height, bool isDepth) {
  GLuint textureId;

  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  GLenum internalFormat = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA8;
  GLenum format = isDepth ? GL_DEPTH_COMPONENT : GL_RGBA;

  glTexImage2D(
    GL_TEXTURE_2D,    // target
    0,                // level : Specifies the level-of-detail number. (mipmapping)
    internalFormat,   // internal format : Specifies the number of color components in the texture.
    width,            // width
    height,           // height
    0,                // border : This value must be 0.
    format,           // format : Specifies the format of the pixel data.
    GL_FLOAT,         // type : Specifies the data type of the pixel data. 
    NULL              // data (void*) : Specifies a pointer to the image data in memory, don't fill it with anything
    );                // if it was an image, give a pointer to the image

    // Poor filtering. Needed !
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

#if DEGUG
    int error;

    if((error = glGetError()) != GL_FALSE) {
      string msg = "error while loading texture : ";
      string err = (const char*) gluErrorString(error);

      throw std::runtime_error(msg + err);
    }
#endif

    glBindTexture(GL_TEXTURE_2D, 0);

    return textureId;
}