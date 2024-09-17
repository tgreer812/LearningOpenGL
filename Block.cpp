#include <memory>
#include "Block.h"
#include "SimpleModel.h"
#include "Mesh.h"
#include "ShaderManager.h"


Block::Block() : Block(glm::vec3(0.0f, 0.0f, 0.0f)) {}

Block::Block(glm::vec3 pos) {
    this->position = pos;

    // Compute the model matrix
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
    modelMatrix = glm::translate(modelMatrix, this->position);

    m_model = std::make_shared<SimpleModel>(cubeModelFile);
    std::shared_ptr<Shader> shader = ShaderManager::Instance().GetShader(
        vertexShader, 
        fragmentShader
    );
    m_material = std::make_shared<Material>(shader);
    m_mesh = std::make_shared<Mesh>(
        m_model->GetVertices(),
        m_model->GetIndices(),
        m_model->GetColors(),
        m_model->GetTextureCoords(),
        modelMatrix,
        m_material
    );
}

std::shared_ptr<Material> Block::GetMaterial() {
    return this->m_material;
}

void Block::Bind() {
    this->m_material->Use();
    this->m_mesh->Bind();

}

// Drawable - returns the number of indices for the block
unsigned int Block::GetSize() {
    return this->m_mesh->Indices.size();
}