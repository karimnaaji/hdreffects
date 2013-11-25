#include "renderer.h"

Renderer::Renderer(int width_, int height_, Camera* camera_) {
	shaderLibrary = new ShaderLibrary();
    camera = camera_;
    width = width_;
    height = height_;

	_shader = NULL;
}

Renderer::~Renderer() {
	delete shaderLibrary;
    delete cubemap;
    delete model;
    delete renderTexture;
    delete bloomPass;
    delete quad;
}

void Renderer::LoadShaders() {
	shaderLibrary->AddShader(string("fresnel"));
    shaderLibrary->AddShader(string("cubemap"));
    shaderLibrary->AddShader(string("bloom"));
}

void Renderer::LoadMeshes() {
    HDRTextureCube* hdrTextureCube = new HDRTextureCube();
    hdrTextureCube->Load(string("uffizi_cross"));
    hdrTextureCube->Init();
    
    MaterialCubeMap* materialCubeMap = new MaterialCubeMap(shaderLibrary->GetShader("cubemap"), hdrTextureCube);

    cubemap = new CubeMap(materialCubeMap);
    cubemap->CreateBufferData();

    Material* materialModel = new Material(shaderLibrary->GetShader("fresnel"));
    materialModel->AddTexture(hdrTextureCube);
    //glm::vec4 materialColour = glm::vec4(1.0);
    //materialModel->SetColour(materialColour);
    model = new Mesh(ObjParser::Parse("sphere+torus"), materialModel);
    model->CreateBufferData();

    Material* materialQuad = new Material(shaderLibrary->GetShader("bloom"));
    quad = new Mesh(Geometries::Quad(1.0f), materialQuad);
    quad->CreateBufferData();
    
    //Material* materialVignette = new Material(shaderLibrary->GetShader("vignette"));
    //vignette = new Mesh(Geometries::Quad(1.0f), materialVignette);
    //vignette->CreateBufferData();
}

void Renderer::Init() {
	glClearColor(56.0/255, 101.0/255, 190.0/255, 1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    LoadShaders();
    LoadMeshes();

    bloomPass = new Framebuffer(width, height);
    renderTexture = new Texture("renderTexture", width, height, GL_RGB16F_ARB);
    renderTexture->Init();
    bloomPass->AttachTexture(renderTexture);
    bloomPass->Init();
}

void Renderer::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bloomPass->Start();
        DrawMesh(cubemap);
        DrawMesh(model);
    bloomPass->End();

    bloomPass->Bind(shaderLibrary->GetShader("bloom"));
    DrawMesh(quad, false);

    //glEnable(GL_BLEND);
    //SetCurrentShader(vignette->GetMaterial()->Bind());
    //vignette->Draw();
    //glDisable(GL_BLEND);
}

void Renderer::DrawMesh(Mesh* mesh, bool sendDefaultUniforms) {
    Shader* shader = mesh->GetMaterial()->Bind();
    if(sendDefaultUniforms) {
        _shader = shader;
        SendDefaultUniforms();
    }
    mesh->Draw();
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
