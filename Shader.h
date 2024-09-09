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
    Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) : programID(0) {
        LoadShaderFiles(vertexShaderFilePath, fragmentShaderFilePath);
    }
    ~Shader();

    bool LoadShaderSource(const std::string& vertexSource, const std::string& fragmentSource);
    bool LoadShaderFiles(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    bool Compile();
    void Bind();
    void Unbind();

    // Uniform setting functions
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetFloat3(const std::string& name, const glm::vec3& value);
    void SetFloat4(const std::string& name, const glm::vec4& value);
    void SetMat3(const std::string& name, const glm::mat3& value);
    void SetMat4(const std::string& name, const glm::mat4& value);

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

