#pragma once
#include "Shader.h"

class ColorShader : public Shader {
public:
    // Default constructor (Black color)
    ColorShader()
        : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

    // Constructor that accepts RGB as integers, with alpha defaulting to 1.0f
    ColorShader(int red, int green, int blue)
        : r(red / 255.0f), g(green / 255.0f), b(blue / 255.0f), a(1.0f) {}

    // Constructor that accepts RGBA as integers
    ColorShader(int red, int green, int blue, int alpha)
        : r(red / 255.0f), g(green / 255.0f), b(blue / 255.0f), a(alpha / 255.0f) {}

    // Constructor that accepts RGB as floats, with alpha defaulting to 1.0f
    ColorShader(float red, float green, float blue)
        : r(red), g(green), b(blue), a(1.0f) {}

    // Constructor that accepts RGBA as floats
    ColorShader(float red, float green, float blue, float alpha)
        : r(red), g(green), b(blue), a(alpha) {}

    // Additional constructor to accept shader source and color in floats
    ColorShader(const std::string& vertexSource, const std::string& fragmentSource, float red, float green, float blue, float alpha)
        : r(red), g(green), b(blue), a(alpha) {
        LoadShaderSource(vertexSource, fragmentSource);
    }

    // Additional constructor to accept shader source and color in ints
    ColorShader(const std::string& vertexSource, const std::string& fragmentSource, int red, int green, int blue, int alpha)
        : r(red / 255.0f), g(green / 255.0f), b(blue / 255.0f), a(alpha / 255.0f) {
        LoadShaderSource(vertexSource, fragmentSource);
    }

    // Override Bind to set color uniforms
    void Bind() override {
        Shader::Bind();
        SetUniform("u_Color", glm::vec4(r, g, b, a));  // Set uniform color (assumes shader expects "u_Color")
    }

    void Unbind() override {
        Shader::Unbind();
    }

private:
    // Private members to store color in RGBA float form
    float r, g, b, a;
};
