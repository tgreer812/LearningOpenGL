#include "TextureShader.h"



/*

#include "Shader.h"
#include <iostream>

// Utility function to check for shader compilation and linking errors
void checkShaderCompileErrors(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    this->VertexShaderPath = vertexShaderPath;
    this->FragmentShaderPath = fragmentShaderPath;
    std::string vertexShaderSource = readFile(vertexShaderPath);
    std::string fragmentShaderSource = readFile(fragmentShaderPath);

    // Compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderSourceCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vShaderSourceCStr, NULL);
    glCompileShader(vertexShader);
    checkShaderCompileErrors(vertexShader, "VERTEX");

    // Compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fShaderSourceCStr, NULL);
    glCompileShader(fragmentShader);
    checkShaderCompileErrors(fragmentShader, "FRAGMENT");

    // Link shaders into a program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkShaderCompileErrors(shaderProgram, "PROGRAM");

    // Set the program ID in the Shader object
    this->ShaderProgram = shaderProgram;

    // Delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(this->ShaderProgram);
}

GLuint Shader::GetShaderProgram() {
    return this->ShaderProgram;
}

void Shader::Use() {
    glUseProgram(this->ShaderProgram);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->ShaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(this->ShaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(this->ShaderProgram, name.c_str()), value);
}

void Shader::setMatrix4(const std::string& name, glm::mat4 value) {
    glUniformMatrix4fv(
        glGetUniformLocation(this->ShaderProgram, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}






*/