#pragma once

#include <string>
#include "Shader.h"
#include "Texture2D.h"
#include "glm/glm.hpp"

class Material
{
public:
    Material() : m_blendFactor(1.0f), m_useTexture(false), m_vertexColor(1.0f, 1.0f, 1.0f) {};
    Material(std::shared_ptr<Shader> shader);

    Material(const Material&) = delete;              // Delete copy constructor
    Material& operator=(const Material&) = delete;   // Delete copy assignment operator

    // Move constructor
    Material(Material&& other) noexcept
        : m_shader(std::move(other.m_shader)),
        m_texture(std::move(other.m_texture)),
        m_vertexColor(std::move(other.m_vertexColor)),
        m_blendFactor(other.m_blendFactor),
        m_useTexture(other.m_useTexture) {
        // You might want to reset the state of the moved-from object
        other.m_blendFactor = 1.0f;
        other.m_useTexture = false;
        other.m_vertexColor = glm::vec3(1.0f, 1.0f, 1.0f);  // Reset to default color
    }

    // Move assignment operator
    Material& operator=(Material&& other) noexcept {
        if (this != &other) {
            m_shader = std::move(other.m_shader);
            m_texture = std::move(other.m_texture);
            m_vertexColor = std::move(other.m_vertexColor);
            m_blendFactor = other.m_blendFactor;
            m_useTexture = other.m_useTexture;

            // Reset moved-from object to default state
            other.m_blendFactor = 1.0f;
            other.m_useTexture = false;
            other.m_vertexColor = glm::vec3(1.0f, 1.0f, 1.0f);
        }
        return *this;
    }

    glm::vec3 GetVertexColor();

    // TODO: update this to vec4 to support alpha channel
    void SetVertexColor(glm::vec3 color);
    void SetTexture(Texture2D texture);
    void SetBlend(float blendAmount);
    //void SetTextureCoords(std::vector<float> texCoords);
    void SetShader(std::shared_ptr<Shader> shader) { this->m_shader = shader; }
    //std::vector<float> GetTextureCoords();

    std::shared_ptr<Shader> m_shader;

    void Use();

private:
    bool m_useTexture;
    
    glm::vec3 m_vertexColor;
    Texture2D m_texture;
    float m_blendFactor;                // Blends the vertex color and the texture. 1.0 is all texture. 0.0 is all color
    //std::vector<float> m_texCoords;
};

