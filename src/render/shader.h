#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>

#include "graphics.h"

using namespace std;

class Shader {
public:
	Shader(string vertexFile, string fragmentFile);
	~Shader(void);

	GLuint Program();
	bool Link();

private:	
	GLuint CreateShader(GLenum type, string& file);
	bool LoadShaderSource(string& file, string& into);
	void SetDefaultAttributes();

	GLuint fragment;
	GLuint vertex;
	GLuint program;
};

#endif