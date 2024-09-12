#pragma once
#include <vector>
#include "glad/glad.h"

class VertexArray {
public:
    // Default constructor
    VertexArray();

    // Constructor that takes vectors of vertices and indices
    VertexArray(const std::vector<float>& vbo, const std::vector<unsigned int>& indices);

    // Prevent copying of VertexArray
    VertexArray(const VertexArray& other) = delete;
    VertexArray& operator=(const VertexArray&) = delete;

    // Allow moving of VertexArray
    VertexArray(VertexArray&& other) noexcept;

    VertexArray& operator=(VertexArray&& other) noexcept;

    // Method to bind the vertex array for rendering
    void Bind();

    void Unbind();

    // Method to update the vertex and index data
    void UpdateData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    // Method to clear the buffer data
    void Clear();

    // Get the size of the indices (for drawing)
    unsigned int GetSize() const;

    // Destructor
    ~VertexArray();

private:
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
    GLuint VAO, VBO, EBO;
    bool dataBuffered;  // Flag to track whether data has been buffered to GPU

    // Internal method to buffer data (called once during initialization or when data is updated)
    void BufferData();
};
