#pragma once
#include "Geometry.h"
#include "Material.h"
#include "VertexArray.h"
#include "Utils.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include <memory>  // Include smart pointers

class Mesh {
public:
    std::vector<float> Vertices, Colors, TextureCoords;
    std::vector<unsigned int> Indices;
    glm::mat4 m_modelMatrix;
    
    Camera* m_camera;

    Mesh(
        const std::vector<float> vertices,
        const std::vector<unsigned int> indices,
        const std::vector<float> colors,
        const std::vector<float> textureCoords,
        const glm::mat4 modelMatrix,
        Material &material,
        Camera &camera
    ) : 
        // Initializer list
        Vertices(vertices), 
        Colors(colors), 
        TextureCoords(textureCoords), 
        Indices(indices), 
        m_camera(&camera), 
        m_modelMatrix(modelMatrix)
    {
        m_material = std::move(material);
        this->initialize();
    }

    // No copying of meshes allowed
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh&) = delete;

    unsigned int Bind() {
        
        this->m_material.Use();
        this->m_material.m_shader.SetMat4("ModelMatrix", m_modelMatrix);
        this->m_material.m_shader.SetMat4("ProjectionMatrix", m_camera->GetProjectionMatrix());
        this->m_material.m_shader.SetMat4("ViewMatrix", m_camera->GetViewMatrix());
        this->vertexArray.Bind();
        

        return this->Indices.size();
    }

    void Unbind() {
        
        this->vertexArray.Unbind();
    }

private:
    void initialize() {
        std::vector<float> vbo = Utils::CreateInterleavedVertexBuffer(
            this->Vertices,
            this->Colors,
            this->TextureCoords
        );
        
        vertexArray = std::move(VertexArray(
            vbo,
            this->Indices
        ));
    }

    bool initialized = false;
    VertexArray vertexArray;
    Material m_material;
};
