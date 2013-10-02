#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include "graphics.h"
#include "hdrtexturecube.h"


using namespace std;

class Shader {
	public:
		Shader(string shaderName);
		~Shader(void);

		GLuint Program() const;
		void Init();
		string GetName() const;
		bool IsInUse() const;

		void SendUniform(string name, HDRTextureCube* hdrTextureCube);
		void SendUniform(string name, float value);
		void SendUniform(string name, glm::mat4 mat);

	private:	
		bool Link();
		GLuint CreateShader(GLenum type, string& file);
		bool LoadShaderSource(string& file, string& into);
		void SetDefaultAttributes();
		GLint Uniform(string uniformName) const;

		GLuint fragment;
		GLuint vertex;
		GLuint program;

		string name;
};

#endif
