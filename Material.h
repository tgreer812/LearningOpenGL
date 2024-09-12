#pragma once

#include <string>
#include "Shader.h"
#include "Texture2D.h"
#include "glm/glm.hpp"

class Material
{
public:
    Material() : m_blendFactor(1.0f), m_useTexture(false), m_vertexColor(1.0f, 1.0f, 1.0f) {};
    Material(Shader shader);

    glm::vec3 GetVertexColor();

    // TODO: update this to vec4 to support alpha channel
    void SetVertexColor(glm::vec3 color);
    void SetTexture(Texture2D texture);
    void SetBlend(float blendAmount);
    //void SetTextureCoords(std::vector<float> texCoords);
    void SetShader(Shader shader) { this->m_shader = shader; }
    //std::vector<float> GetTextureCoords();

    Shader GetShader();

    void Use();

private:
    bool m_useTexture;
    Shader m_shader;
    glm::vec3 m_vertexColor;
    Texture2D m_texture;
    float m_blendFactor;                // Blends the vertex color and the texture. 1.0 is all texture. 0.0 is all color
    std::vector<float> m_texCoords;
};

