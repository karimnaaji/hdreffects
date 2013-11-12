#include "renderer.h"

Renderer::Renderer(int width, int height, Camera* camera_) {
	shaderLibrary = new ShaderLibrary();

    camera = camera_;

	_shader = NULL;
}

Renderer::~Renderer() {
	delete shaderLibrary;
    delete cubemap;
    delete sphere;
    delete vignette;
}

void Renderer::LoadShaders() {
	shaderLibrary->AddShader(string("fresnel"));
    shaderLibrary->AddShader(string("cubemap"));
    shaderLibrary->AddShader(string("vignette"));
}

void Renderer::LoadMeshes() {
    HDRTextureCube* hdrTextureCube = new HDRTextureCube();
    hdrTextureCube->Load(string("uffizi_cross"));
    
    MaterialCubeMap* materialCubeMap = new MaterialCubeMap(shaderLibrary->GetShader("cubemap"), hdrTextureCube);

    cubemap = new CubeMap(materialCubeMap);
    cubemap->CreateBufferData();

    Material* materialSphere = new Material(shaderLibrary->GetShader("fresnel"));
    materialSphere->AddTexture(hdrTextureCube);
    //glm::vec4 materialColour = glm::vec4(1.0);
    //materialSphere->SetColour(materialColour);
    sphere = new Mesh(ObjParser::Parse("bunny"), materialSphere);
    sphere->CreateBufferData();
    
    Material* materialVignette = new Material(shaderLibrary->GetShader("vignette"));
    vignette = new Mesh(Geometries::Quad(1.0f), materialVignette);
    vignette->CreateBufferData();
}

void Renderer::Init() {
	glClearColor(1, 1, 1, 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LoadShaders();
    LoadMeshes();
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderCubeMap();

    SetCurrentShader(sphere->GetMaterial()->Bind());
    sphere->Draw();

    //glEnable(GL_BLEND);
    //SetCurrentShader(vignette->GetMaterial()->Bind());
    //vignette->Draw();
    //glDisable(GL_BLEND);
}

void Renderer::SetCurrentShader(Shader* shader) {
    _shader = shader;
    SendDefaultUniforms();
}

void Renderer::RenderCubeMap() {
    SetCurrentShader(cubemap->GetMaterial()->Bind());
    cubemap->Draw();
}

void Renderer::SendDefaultUniforms() {
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = projection * view * model;
    glm::mat3 normalMatrix = glm::inverse(glm::transpose(glm::mat3(mvp)));

    _shader->SendUniform("mvp", mvp);
    _shader->SendUniform("normalMatrix", normalMatrix);
    _shader->SendUniform("camPosition", camera->GetPosition());
}

void Renderer::CreateFrameBuffer(GLuint renderTexture) {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

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
