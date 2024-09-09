#pragma once
#include "Geometry.h"
#include "Material.h"
#include "VertexArray.h"
#include "Utils.h"

template <typename T>
class Mesh {
public:
    Mesh(const T& geometry, Material& material)
        : m_geometry(geometry), m_material(material) {
        // Initialize VAO and buffers during construction
        InitializeBuffers();
    }

    // Bind the material and VAO for drawing
    unsigned int Bind() {
        m_material.Use();    // Bind the material (and thus the shader)

        // Just bind the pre-initialized VAO
        va.Use();           // Bind the vertex array object (VAO)
        return va.GetSize(); // Return the size of the indices (for draw call)
    }

    // Getter for the material
    Material& GetMaterial() {
        return m_material;
    }

private:
    // Method to initialize the VAO, VBO, and EBO
    void InitializeBuffers() {
        std::vector<float> positions = m_geometry.GetVertexPositions();
        std::vector<unsigned int> indices = m_geometry.GetIndices();
        glm::vec3 color = m_material.GetVertexColor();

        std::vector<float> vertexColors = Utils::FillVector3(color, positions.size() / 3);
        std::vector<float> textureCoords = m_material.GetTextureCoords();

        std::vector<float> vbo = Utils::CreateInterleavedVertexBuffer(positions, vertexColors, textureCoords);

        // Initialize the vertex array (VAO) and buffers (VBO, EBO)
        va = VertexArray(vbo, indices);
    }

    T m_geometry;
    Material m_material;
    VertexArray va;  // Store this as a member variable, initialized once
};
