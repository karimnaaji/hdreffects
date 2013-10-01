#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <string>

#include "graphics.h"

#define VERT_EXT 	".vert"
#define FRAG_EXT 	".frag"

#define RELATIVE_PATH   "shaders/"

using namespace std;

class Shader {
	public:
		Shader(string shaderName);
		~Shader(void);

		GLuint Program();
		void Init();
		string GetName() const;
		
	private:	
		bool Link();
		GLuint CreateShader(GLenum type, string& file);
		bool LoadShaderSource(string& file, string& into);
		void SetDefaultAttributes();

		GLuint fragment;
		GLuint vertex;
		GLuint program;

		string name;
};

#endif
