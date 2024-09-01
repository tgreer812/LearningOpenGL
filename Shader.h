#pragma once
#include <string>
#include "Utils.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

class Shader
{
public:

	GLuint ShaderProgram;
	
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

	~Shader();

	// Returns a GLuint representing a glShaderProgram
	GLuint GetShaderProgram();

	void Use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setMatrix4(const std::string& name, glm::mat4 matrix);



private:
	std::string VertexShaderPath;
	std::string FragmentShaderPath;
};

