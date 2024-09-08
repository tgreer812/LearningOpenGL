#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include <memory>  // Required for std::shared_ptr

class Texture2DShader : public Shader {
public:
    // Constructor that accepts shader source code as a string and a Texture2D object
    Texture2DShader(const std::string& shaderSource, std::shared_ptr<Texture2D> texture)
        : Shader(shaderSource), texture(texture) {}

    // Constructor that accepts a FILE* and a Texture2D object
    Texture2DShader(FILE* shaderFile, std::shared_ptr<Texture2D> texture)
        : Shader(shaderFile), texture(texture) {}

    // Constructor that accepts an ifstream and a Texture2D object
    Texture2DShader(std::ifstream& shaderStream, std::shared_ptr<Texture2D> texture)
        : Shader(shaderStream), texture(texture) {}

    // Constructor that accepts a file path and a Texture2D object
    Texture2DShader(const char* filePath, std::shared_ptr<Texture2D> texture)
        : Shader(filePath), texture(texture) {}

    // Virtual methods to be implemented
    void Bind() override;
    void Unbind() override;

private:
    std::shared_ptr<Texture2D> texture;
};

