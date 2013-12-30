#include "shader.h"

Shader::Shader(string shaderName) : name(shaderName) {}

void Shader::Init() {
	program = glCreateProgram();
	
	string fragName = name + string(FRAG_EXT);
	string vertName = name + string(VERT_EXT);

	vertex = CreateShader(GL_VERTEX_SHADER, vertName);
	fragment = CreateShader(GL_FRAGMENT_SHADER, fragName);

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	// must be done before linking
	SetDefaultAttributes();

	Link();
}

Shader::~Shader(void) {
	glDetachShader(program, fragment);
	glDeleteShader(fragment);

	glDetachShader(program, vertex);
	glDeleteShader(vertex);

	glDeleteProgram(program);
}

string Shader::GetName() const {
	return name;
}

GLuint Shader::Program() const {
	return program;
}

void Shader::Use() const {
    if(!IsInUse())
	    glUseProgram(Program());
}

void Shader::Release() const {
    glUseProgram(0);
}

bool Shader::IsInUse() const {
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    return (Program() == (GLuint)currentProgram);
}

void Shader::Link() {
	glLinkProgram(program);

	GLint code;
	glGetProgramiv(program, GL_LINK_STATUS, &code);

	if(!code) {
		throw runtime_error("Link shader failure (" + name + ")"); 
	}
}

void Shader::SetDefaultAttributes() {
	glBindAttribLocation(program, VERTEX_BUFFER, "position");
	glBindAttribLocation(program, TEXTURE_BUFFER, "uv");
	glBindAttribLocation(program, COLOUR_BUFFER, "colour");
    glBindAttribLocation(program, NORMAL_BUFFER, "normal");
}

void Shader::LoadShaderSource(string& path, string& into) {
	ifstream file;
	string buffer;

	file.open(path.c_str());

	if(!file.is_open()) {
		throw runtime_error("Opening file failure" + path + " (" + name + ")"); 
	}

	while(!file.eof()) {
		getline(file, buffer);
		into += buffer + "\n";
	}

	file.close();
}

GLuint Shader::CreateShader(GLenum type, string& file) {
	string path = string(SHADERS_RELATIVE_PATH) + file;	
	string source;

	LoadShaderSource(path, source);

	GLuint shader = glCreateShader(type);

	const GLchar* chars = source.c_str();

	glShaderSource(shader, 1, &chars, NULL);
	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE) {
		char error[512];

		glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        cerr << "In shader: " << file << endl;
		cerr << error << endl;
		throw runtime_error("Can't compile shader " + file + " (" + name + ")");
	} 

	return shader;
}

GLint Shader::Uniform(string uniformName) const {
    GLint uniform = glGetUniformLocation(program, uniformName.c_str());

    //if(uniform < 0) {
    //	throw runtime_error("Uniform variable not found : " + uniformName + " (" + name + ")");
    //}

    return uniform;
}

void Shader::SendUniform(string name, glm::mat4 mat) {
	assert(IsInUse());
    glUniformMatrix4fv(Uniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SendUniform(string name, glm::mat3 mat) {
    assert(IsInUse());
    glUniformMatrix3fv(Uniform(name), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SendUniform(string name, float value) {
	assert(IsInUse());
    glUniform1f(Uniform(name), value);
}

void Shader::SendUniform(string name, int value) {
	assert(IsInUse());
    glUniform1i(Uniform(name), value);
}

void Shader::SendUniform(string name, Texture* texture) {
	assert(IsInUse());
	glUniform1i(Uniform(name), texture->TextureIndex());
}

void Shader::SendUniform(string name, glm::vec2 vec) {
	assert(IsInUse());
	glUniform2f(Uniform(name), vec[0], vec[1]);
}

void Shader::SendUniform(string name, glm::vec3 vec) {
	assert(IsInUse());
	glUniform3f(Uniform(name), vec[0], vec[1], vec[2]);
}

void Shader::SendUniform(string name, glm::vec4 vec) {
	assert(IsInUse());
	glUniform4f(Uniform(name), vec[0], vec[1], vec[2], vec[3]);
}

