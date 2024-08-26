#include "Shader.h"

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	this->VertexShaderPath = vertexShaderPath;
	this->FragmentShaderPath = fragmentShaderPath;
	std::string vertexShaderSource = readFile(vertexShaderPath);
	std::string fragmentShaderSource = readFile(fragmentShaderPath);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vShaderSourceCStr = vertexShaderSource.c_str();
	glShaderSource(vertexShader, 1, &vShaderSourceCStr, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fShaderSourceCStr = fragmentShaderSource.c_str();
	glShaderSource(fragmentShader, 1, &fShaderSourceCStr, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	this->ShaderProgram = shaderProgram;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader() {
	glDeleteProgram(this->ShaderProgram);
}

GLuint Shader::GetShaderProgram() {
	return this->ShaderProgram;
}