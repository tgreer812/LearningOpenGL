#pragma once
#include <vector>
#include "glad/glad.h"

class VertexArray {
public:
    // Default constructor
    VertexArray();

    // Constructor that takes vectors of vertices and indices
    VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    unsigned int GetSize();

    // Destructor
    ~VertexArray();

    // Method to bind and use the vertex array
    void Use();

private:
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    GLuint VAO, VBO, EBO;
};
