#include "Material.h"
#include "glm/glm.hpp"

Material::Material(Shader shader) : m_shader(shader), m_useTexture(false), m_blendFactor(0.0), m_vertexColor(1.0, 1.0, 1.0) {

}


void Material::SetVertexColor(glm::vec3 color) {
    this->m_vertexColor = color;
}


void Material::SetTexture(Texture2D texture) {
    this->m_useTexture = true;
    this->m_texture = texture;
}

//void Material::Set


void Material::SetBlend(float blendFactor) {
    m_blendFactor = glm::mod(blendFactor, 1.0f);
}


void Material::Use() {
    this->m_shader.Bind();
    if (this->m_useTexture) { this->m_texture.Bind(); }
    this->m_shader.SetInt("aTexture", this->m_texture.GetTextureUnit());
    this->m_shader.SetFloat("blendFactor", this->m_blendFactor);
}