// ShaderManager.cpp
#include "ShaderManager.h"
#include <functional> // For std::hash
#include <sstream>    // For std::stringstream
#include <iostream>   // For error messages

// Singleton instance
ShaderManager& ShaderManager::Instance() {
    static ShaderManager instance;
    return instance;
}

std::shared_ptr<Shader> ShaderManager::GetShader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Generate a unique key for the shader combination
    std::string key = GenerateShaderKey(vertexPath, fragmentPath);

    {
        // Lock the mutex for thread safety
        std::lock_guard<std::mutex> lock(cacheMutex);

        // Check if the shader is already loaded
        auto it = shaderCache.find(key);
        if (it != shaderCache.end()) {
            // Return the existing shader
            return it->second;
        }
    }

    // Shader not found, load and compile it
    std::shared_ptr<Shader> shader = std::make_shared<Shader>();

    // Load shader source from files
    if (!shader->LoadShaderFiles(vertexPath, fragmentPath)) {
        std::cerr << "Error: Failed to load shader files: " << vertexPath << ", " << fragmentPath << std::endl;
        return nullptr;
    }

    // Compile the shader
    if (!shader->Compile()) {
        std::cerr << "Error: Failed to compile shader: " << key << std::endl;
        return nullptr;
    }

    {
        // Lock the mutex before modifying the cache
        std::lock_guard<std::mutex> lock(cacheMutex);
        // Store the shader in the cache
        shaderCache[key] = shader;
    }

    return shader;
}

void ShaderManager::Clear() {
    // Lock the mutex for thread safety
    std::lock_guard<std::mutex> lock(cacheMutex);

    // Clear the shader cache
    shaderCache.clear();
}

std::string ShaderManager::GenerateShaderKey(const std::string& vertexPath, const std::string& fragmentPath) {
    // Generate a unique key by hashing the concatenated file paths
    std::hash<std::string> hasher;
    size_t hashValue = hasher(vertexPath + fragmentPath);

    // Convert hash value to string
    std::stringstream ss;
    ss << hashValue;

    return ss.str();
}
