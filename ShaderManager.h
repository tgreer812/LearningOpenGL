// ShaderManager.h
#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <mutex>
#include "Shader.h"

class ShaderManager {
public:
    // Singleton access method
    static ShaderManager& Instance();

    // Deleted methods to prevent copying
    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    // Method to get or load a shader
    std::shared_ptr<Shader> GetShader(const std::string& vertexPath, const std::string& fragmentPath);

    // Optional method to clear all shaders (e.g., on application shutdown)
    void Clear();

private:
    // Private constructor
    ShaderManager() = default;
    ~ShaderManager() = default;

    // Map to store shaders with a unique key
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaderCache;

    // Mutex for thread safety
    std::mutex cacheMutex;

    // Helper function to generate a unique key for shader combinations
    std::string GenerateShaderKey(const std::string& vertexPath, const std::string& fragmentPath);
};
