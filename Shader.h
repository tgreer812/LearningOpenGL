#pragma once
#include <string>
#include <unordered_map>
#include "glad/glad.h"
#include <glm/glm.hpp>  // For matrix and vector types
#include <glm/ext.hpp>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader {
public:
    Shader() : programID(0) {}
    virtual ~Shader();

    bool LoadShaderSource(const std::string& vertexSource, const std::string& fragmentSource);
    bool LoadShaderFiles(const std::string& vertexFilePath, const std::string& fragmentFilePath);

    bool Compile();
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    // Uniform setting functions
    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, float value);
    void SetUniform(const std::string& name, const glm::vec3& value);
    void SetUniform(const std::string& name, const glm::vec4& value);
    void SetUniform(const std::string& name, const glm::mat4& value);


    // Error checking
    std::string GetErrorLog() const;

    // Utility
    std::string ReadFile(const std::string& filePath);

protected:
    virtual void PreLink() {};      // Hook for derived classes to set up attributes before linking
    virtual void PostLink() {};     // Hook for derived classes to validate uniforms after linking

    GLuint programID;
    std::unordered_map<std::string, GLint> uniformLocations;

private:
    std::string vertexSourceCode;
    std::string fragmentSourceCode;
    bool isCompiled = false;        // flag to track if the shader has been compiled


    bool CheckShaderCompileStatus(GLuint shaderID);
    bool CheckProgramLinkStatus(GLuint programID);
};

