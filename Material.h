#pragma once

#include <string>
#include "Shader.h"
#include "Texture2D.h"
#include "glm/glm.hpp"

class Material
{
public: 
    Material(Shader shader);

    // TODO: update this to vec4 to support alpha channel
    void SetVertexColor(glm::vec3 color);
    void SetTexture(Texture2D texture);
    void SetBlend(float blendAmount);

    void Use();

private:
    bool m_useTexture;
    Shader m_shader;
    glm::vec3 m_vertexColor;
    Texture2D m_texture;
    float m_blendFactor;
};

