#pragma once
#include "Material.h"
#include "VertexArray.h"
#include "Utils.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "World.h"
#include <memory>  // Include smart pointers

class Mesh {
public:
    std::vector<float> Vertices, Colors, TextureCoords;
    std::vector<unsigned int> Indices;
    glm::mat4 m_modelMatrix;        

    Mesh(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        const std::vector<float>& colors,
        const std::vector<float>& textureCoords,
        const glm::mat4& modelMatrix,
        //const glm::mat4& projectionMatrix,
        //const glm::mat4& viewMatrix,
        std::shared_ptr<Material> material
    ) : 
        // Initializer list
        Vertices(vertices), 
        Colors(colors), 
        TextureCoords(textureCoords), 
        Indices(indices), 
        m_modelMatrix(modelMatrix),
        m_material(material)
    {
        
        this->initialize();
    }

    unsigned int Bind() {

        if (!this->initialized) {
            std::cout << "WARNING: Mesh not initialized!" << std::endl;
        }
        
        this->m_material->Use();
        this->m_material->m_shader->SetMat4("modelMatrix", m_modelMatrix);
        this->m_material->m_shader->SetMat4("projectionMatrix", World::GetInstance().GetCamera().GetProjectionMatrix());
        this->m_material->m_shader->SetMat4("viewMatrix", World::GetInstance().GetCamera().GetViewMatrix());
        this->m_vertexArray->Bind();
        

        return this->Indices.size();
    }

    void Unbind() {
        
        this->m_vertexArray->Unbind();
    }

private:
    void initialize() {
        std::vector<float> vbo = Utils::CreateInterleavedVertexBuffer(
            this->Vertices,
            this->Colors,
            this->TextureCoords
        );
        
        m_vertexArray = std::make_shared<VertexArray>(VertexArray(
            vbo,
            this->Indices
        ));
        this->initialized = true;
    }

    bool initialized = false;
    std::shared_ptr<VertexArray> m_vertexArray;
    //Material* m_material;
    std::shared_ptr<Material> m_material;
};
