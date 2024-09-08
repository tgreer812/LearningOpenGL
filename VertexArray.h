#pragma once
#include <vector>
#include "glad/glad.h"

class VertexArray {
public:
    // Default constructor
    VertexArray();

    // Constructor that takes vectors of vertices and indices
    VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    // Destructor
    ~VertexArray();

    // Method to bind and use the vertex array
    void Use();

private:
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
    GLuint VAO, VBO, EBO;
};
