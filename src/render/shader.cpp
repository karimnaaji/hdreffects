#include "shader.h"

Shader::Shader(string vertexFile, string fragmentFile) {
	program = glCreateProgram();
	vertex = CreateShader(GL_VERTEX_SHADER, vertexFile);
	fragment = CreateShader(GL_FRAGMENT_SHADER, fragmentFile);

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	SetDefaultAttributes();
}

Shader::~Shader(void) {
	glDetachShader(program, fragment);
	glDeleteShader(fragment);

	glDetachShader(program, vertex);
	glDeleteShader(vertex);

	glDeleteProgram(program);
}

GLuint Shader::Program() {
	return program;
}

bool Shader::Link() {
	glLinkProgram(program);

	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);

	return code == GL_TRUE ? true : false ;
}

/* Must be done before linking */
void Shader::SetDefaultAttributes() {
	/* another possibility would be to let opengl 
	decide for the locations and query it after */
	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, TEXTURE_BUFFER, "uv");
	glBindAttribLocation(program, COLOUR_BUFFER, "colour");
}

bool Shader::LoadShaderSource(string& path, string& into) {
	ifstream file;
	string buffer;

	cout << path << " :" << endl;

	file.open(path.c_str());

	if(!file.is_open()) {
		cout << "Opening file failure" << endl;
		return false;
	}

	while(!file.eof()) {
		getline(file, buffer);
		into += buffer + "\n";
	}

	file.close();
	//cout << into << endl << endl;
	cout << "Shader source loaded" << endl;

	return true;
}

GLuint Shader::CreateShader(GLenum type, string& file) {
	string source;

	if(!LoadShaderSource(file, source)) {
		cout << "Creation of shader failed" << endl;
		return 0;
	}

	GLuint shader = glCreateShader(type);

	const GLchar* chars = source.c_str();

	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE) {
		char error[512];

		glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cout << "Impossible de compiler le shader" << endl;
		cout << file << " : " << error;

		return 0;
	} 

	cout << "Shader compilation successfull" << endl;

	return shader;
}