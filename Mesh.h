#pragma once
#include "Geometry.h"
#include "Material.h"
#include "VertexArray.h"
#include "Utils.h"

template <typename T>
class Mesh {
public:

    Mesh(const T& geometry, Material& material) {
        this->m_geometry = geometry;
        this->m_material = material;
    }

    void Bind() {
        std::vector<float> positions = this->m_geometry.GetVertexPositions();
        std::vector<unsigned int> indices = this->m_geometry.GetIndices();
        glm::vec3 color = this->m_material.GetVertexColor();

        // I KNOW this is going to cause problems for me later but meh
        std::vector<float> vertexColors = Utils::FillVector3(color, positions.size() / 3);
        std::vector<float> textureCoords = this->m_material.GetTextureCoords();

        std::vector<float> vbo = Utils::CreateInterleavedVertexBuffer(
            positions,
            vertexColors,
            textureCoords
        );

        this->m_material.Use();
        VertexArray va = VertexArray(vbo, indices);
        va.Use();

    }

    T GetGeometry() { return m_geometry; }
    Material GetMaterial() { return this->m_material; }


private:
    T m_geometry;
    Material m_material;
    VertexArray va;
};