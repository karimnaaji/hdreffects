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
