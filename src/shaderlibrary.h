#ifndef SHADER_LIBRARY_H
#define SHADER_LIBRARY_H

#include <map>
#include <string>
#include "shader.h"

using namespace std;

class ShaderLibrary {
	public:
		ShaderLibrary();
		~ShaderLibrary();

		void AddShader(string shaderName);

		Shader* GetShader(string shaderName) const;
	private:
		map<string, Shader*> shaders;
};

#endif
