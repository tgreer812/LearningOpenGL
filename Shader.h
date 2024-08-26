#pragma once
#include <string>
#include "Utils.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Shader
{
public:

	GLuint ShaderProgram;
	
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

	~Shader();

	// Returns a GLuint representing a glShaderProgram
	GLuint GetShaderProgram();

	void Use();

private:
	std::string VertexShaderPath;
	std::string FragmentShaderPath;
};

