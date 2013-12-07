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
    delete quad;
    delete writeFBO;
    delete readFBO;
    for(int i = 0; i < MAX_DOWNSCALE_FBO; ++i) {
        delete downScaleFBO[i];
    }
}

void Renderer::LoadShaders() {
	shaderLibrary->AddShader(string("fresnel"));
    shaderLibrary->AddShader(string("cubemap"));
    shaderLibrary->AddShader(string("compose"));
    shaderLibrary->AddShader(string("brightpass"));
    shaderLibrary->AddShader(string("blur"));
    shaderLibrary->AddShader(string("default"));
    shaderLibrary->AddShader(string("bloom"));
    shaderLibrary->AddShader(string("tonemap"));
    shaderLibrary->AddShader(string("ghost"));
    shaderLibrary->AddShader(string("rgbshift"));
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
    model = new Mesh(ObjParser::Parse("sphere"), materialModel);
    model->CreateBufferData();

    Material* materialQuad = new Material();
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

    Texture* renderTexture;

    writeFBO = new Framebuffer(width, height);
    readFBO = new Framebuffer(width, height);
    mainFBO = new Framebuffer(width, height);
    
    for(int i = 0; i < MAX_DOWNSCALE_FBO; ++i) {
        downScaleFBO[i] = new Framebuffer(width, height);
        renderTexture = new Texture("renderTexture", width, height, GL_RGB16F_ARB);
        renderTexture->Init();
        downScaleFBO[i]->AttachTexture(renderTexture);
        downScaleFBO[i]->Init();
    }

    renderTexture = new Texture("renderTexture", width, height, GL_RGB16F_ARB);
    renderTexture->Init();
    writeFBO->AttachTexture(renderTexture);
    renderTexture = new Texture("renderTexture", width, height, GL_RGB16F_ARB);
    renderTexture->Init();
    readFBO->AttachTexture(renderTexture);
    renderTexture = new Texture("renderTexture", width, height, GL_RGB16F_ARB);
    renderTexture->Init();
    mainFBO->AttachTexture(renderTexture);

    writeFBO->Init();
    readFBO->Init();
    mainFBO->Init();
}

void Renderer::SwapBuffers() {
    Framebuffer* tmp = readFBO;
    readFBO = writeFBO;
    writeFBO = tmp;
}

void Renderer::Render(float time) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mainFBO->Start();
        DrawMesh(cubemap);
        DrawMesh(model);
    mainFBO->End();

    SwapBuffers();
    
    Framebuffer* buffer;
    if(doBloom) {
        BrightPass(brightThreshold);
        //BloomPass(time);

        float downScale = 4.0;
        BrightPass(6.0);
        writeFBO->Start(1/downScale);
            readFBO->Bind(shaderLibrary->GetShader("ghost"), glm::vec2(width/downScale, height/downScale));
            quad->GetMaterial()->SetShader(shaderLibrary->GetShader("ghost"));
            DrawMesh(quad, false);
        writeFBO->End();

        SwapBuffers();

        for(int j = 0; j < 3; ++j) {
            writeFBO->Start(1/downScale);
                readFBO->Bind(shaderLibrary->GetShader("blur"), glm::vec2(width/downScale, height/downScale));
                quad->GetMaterial()->SetShader(shaderLibrary->GetShader("blur"));
                DrawMesh(quad, false);
            writeFBO->End();

            SwapBuffers();
        }

        writeFBO->Start();
            readFBO->Bind(shaderLibrary->GetShader("rgbshift"));
            quad->GetMaterial()->SetShader(shaderLibrary->GetShader("rgbshift"));
            DrawMesh(quad, false);
        writeFBO->End();

        SwapBuffers();
        
        writeFBO->Start();
            mainFBO->Bind(shaderLibrary->GetShader("compose"), string("sampler2"));
            readFBO->GetRenderTexture()->SetTextureIndex(1);
            readFBO->Bind(shaderLibrary->GetShader("compose"), string("sampler1"));
            quad->GetMaterial()->SetShader(shaderLibrary->GetShader("compose"));
            DrawMesh(quad, false);
        writeFBO->End();

        readFBO->GetRenderTexture()->SetTextureIndex(0);
        
        SwapBuffers();
        
        buffer = readFBO;
    } else {
        buffer = mainFBO;
    }
    
    /*float downScale = height;
    writeFBO->Start(1/downScale);
        buffer->Bind(shaderLibrary->GetShader("default"), glm::vec2(width/downScale, height/downScale));
        quad->GetMaterial()->SetShader(shaderLibrary->GetShader("default"));
        DrawMesh(quad, false);
    writeFBO->End();

    SwapBuffers();
    */
 /*   
    writeFBO->Start();
        mainFBO->Bind(shaderLibrary->GetShader("tonemap"));
        quad->GetMaterial()->SetShader(shaderLibrary->GetShader("tonemap"));
        DrawMesh(quad, false);
    writeFBO->End();

    SwapBuffers();
*/
    readFBO->Bind(shaderLibrary->GetShader("default"));
    quad->GetMaterial()->SetShader(shaderLibrary->GetShader("default"));
    DrawMesh(quad, false);

    //glEnable(GL_BLEND);
    //SetCurrentShader(vignette->GetMaterial()->Bind());
    //vignette->Draw();
    //glDisable(GL_BLEND);
}

void Renderer::BrightPass(float threshold) {
    Shader* brightpass = shaderLibrary->GetShader("brightpass");

    writeFBO->Start();
        mainFBO->Bind(brightpass);
        brightpass->SendUniform("threshold", threshold);
        quad->GetMaterial()->SetShader(brightpass);
        DrawMesh(quad, false);
    writeFBO->End();

    SwapBuffers();
}

void Renderer::BloomPass(float time) {
    Shader* blur = shaderLibrary->GetShader("blur");
    Shader* compose = shaderLibrary->GetShader("compose");
    Shader* bloom = shaderLibrary->GetShader("bloom");

    float downScale = 1.0;
    for(int i = 0; i < MAX_DOWNSCALE_FBO; ++i) {
        downScale *= 2.0;
        downScaleFBO[i]->Start(1/downScale);
            readFBO->Bind(shaderLibrary->GetShader("default"), glm::vec2(width/downScale, height/downScale));
            quad->GetMaterial()->SetShader(shaderLibrary->GetShader("default"));
            DrawMesh(quad, false);
        downScaleFBO[i]->End();
    }

    Framebuffer* lowResFBO = downScaleFBO[MAX_DOWNSCALE_FBO - 1];

    writeFBO->Start(1/downScale);
        lowResFBO->Bind(shaderLibrary->GetShader("default"), glm::vec2(width/downScale, height/downScale));
        quad->GetMaterial()->SetShader(shaderLibrary->GetShader("default"));
        DrawMesh(quad, false);
    writeFBO->End();

    SwapBuffers();

    for(int i = MAX_DOWNSCALE_FBO - 1; i >= 1; i--) {
        for(int j = 0; j < blurPass; ++j) {
            writeFBO->Start(1/downScale);
                readFBO->Bind(blur, glm::vec2(width/downScale, height/downScale));
                quad->GetMaterial()->SetShader(blur);
                DrawMesh(quad, false);
            writeFBO->End();

            SwapBuffers();
        }

        writeFBO->Start(1/(downScale/2));
            readFBO->Bind(compose, string("sampler2"));
            downScaleFBO[i-1]->GetRenderTexture()->SetTextureIndex(1);
            downScaleFBO[i-1]->Bind(compose, glm::vec2(width/(downScale/2), height/(downScale/2)), string("sampler1"));
            quad->GetMaterial()->SetShader(compose);
            DrawMesh(quad, false);
        writeFBO->End();

        SwapBuffers();
        downScale /= 2;
    }

    writeFBO->Start();
        mainFBO->Bind(bloom, string("tex"));
        readFBO->GetRenderTexture()->SetTextureIndex(1);
        readFBO->Bind(bloom, string("bloom"));
        bloom->SendUniform("bloomFactor", bloomFactor);
        bloom->SendUniform("addNoise", addNoise);
        bloom->SendUniform("time", time);
        quad->GetMaterial()->SetShader(bloom);
        DrawMesh(quad, false);
    writeFBO->End();

    readFBO->GetRenderTexture()->SetTextureIndex(0);

    SwapBuffers();
}

void Renderer::DrawMesh(Mesh* mesh, bool sendDefaultUniforms) {
    Shader* shader = mesh->GetMaterial()->Bind();
    if(sendDefaultUniforms) {
        _shader = shader;
        SendDefaultUniforms();
        mesh->Draw();
    } else {
        mesh->Draw();
        /*for(int i = 0; i < 4; i++) {
            glm::vec3 shift = glm::vec3((i % 2) * 0.5 / width, (i / 2) * 0.5 / height, 0);
            glm::mat4 aa = glm::translate(glm::mat4(1.0), shift);
            glm::mat4 view = camera->GetViewMatrix();
            glm::mat4 projection = camera->GetProjectionMatrix();
            glm::mat4 mvp = aa * projection * view;
            shader->SendUniform("aamvp", mvp);
            mesh->Draw();
            glAccum(i ? GL_ACCUM : GL_LOAD, 0.25);
        }
        glAccum(GL_RETURN, 1);
        */
    }
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
