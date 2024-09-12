#include "Material.h"
#include "glm/glm.hpp"

Material::Material(Shader shader) : m_shader(shader), m_useTexture(false), m_blendFactor(0.0), m_vertexColor(1.0, 1.0, 1.0) {

}

glm::vec3 Material::GetVertexColor() { return this->m_vertexColor; }

void Material::SetVertexColor(glm::vec3 color) {
    this->m_vertexColor = color;
}

Shader Material::GetShader() { return this->m_shader; }

void Material::SetTexture(Texture2D texture) {
    this->m_useTexture = true;
    this->m_texture = texture;
}

//void Material::SetTextureCoords(std::vector<float> texCoords) {
//    this->m_texCoords = texCoords;
//}

//std::vector<float> Material::GetTextureCoords() {
//    return this->m_texCoords;
//}

void Material::SetBlend(float blendFactor) {
    // Clamp the blend factor to be between 0.0f and 1.0f
    m_blendFactor = glm::clamp(blendFactor, 0.0f, 1.0f);
}

void Material::Use() {
    this->m_shader.Bind();
    this->m_shader.SetBool("useTexture", this->m_useTexture);
    if (this->m_useTexture) { 
        
        this->m_texture.Bind();
        this->m_shader.SetInt("aTexture", this->m_texture.GetTextureUnit());
    }
    this->m_shader.SetFloat("blendFactor", this->m_blendFactor);
}