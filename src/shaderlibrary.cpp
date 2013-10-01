#include "shaderlibrary.h"

ShaderLibrary::ShaderLibrary() {}

ShaderLibrary::~ShaderLibrary() {
	map<string, Shader*>::iterator it;
	for(it = shaders.begin(); it != shaders.end(); ++it) {
		delete it->second;
	}	
	shaders.clear();
}

void ShaderLibrary::AddShader(string shaderName) {
	Shader* shader = new Shader(shaderName);
	cout << "Init shader" << endl;
	shader->Init();
	cout << "Adding " << shaderName << " into shader library" << endl;
	shaders.insert(pair<string, Shader*>(shaderName, shader));
}

Shader* ShaderLibrary::GetShader(string shaderName) const {
	Shader* shader = shaders.find(shaderName)->second;

    if(shader == NULL) {
        throw new runtime_error("Didn't found shader " + shaderName + " in the shader library");
    }
    cout << "Shader lib : getting " << shaderName << endl;
    return shader;
}

