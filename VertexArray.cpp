#include "VertexArray.h"

// Default constructor
VertexArray::VertexArray()
    : VAO(0), VBO(0), EBO(0) {
    // Initialize empty vectors for vertices and indices
    m_vertices = std::vector<float>();
    m_indices = std::vector<unsigned int>();
}

VertexArray::VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : m_vertices(vertices), m_indices(indices), VAO(0), VBO(0), EBO(0) {
}

VertexArray::~VertexArray() {
    // Cleanup: Delete OpenGL buffers if they were generated
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);
}

unsigned int VertexArray::GetSize() {
    return this->m_indices.size();
}

void VertexArray::Use() {
    // Generate buffers if they haven't been generated yet
    if (VAO == 0) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
    }

    // Bind vertex array object
    glBindVertexArray(VAO);

    // Bind and copy the vertices into the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        m_vertices.size() * sizeof(float),  // Correct size in bytes
        m_vertices.data(),
        GL_STATIC_DRAW
    );

    // Bind the EBO and copy the indices into it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        m_indices.size() * sizeof(unsigned int),  // Correct size in bytes
        m_indices.data(),
        GL_STATIC_DRAW
    );

    // Now set the vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(
        0,                   // Attribute index 0 corresponds to position
        3,                   // Size (3 components per vertex)
        GL_FLOAT,            // Type (float)
        GL_FALSE,            // Don't normalize
        8 * sizeof(float),   // Stride (each vertex has 8 floats: 3 for position, 3 for color, 2 for texture)
        (void*)0             // Offset to the first component (position starts at 0)
    );
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(
        1,                               // Attribute index 1 corresponds to color
        3,                               // Size (3 components per vertex)
        GL_FLOAT,                        // Type (float)
        GL_FALSE,                        // Don't normalize
        8 * sizeof(float),               // Stride (each vertex has 8 floats)
        (void*)(3 * sizeof(float))       // Offset (color starts after the first 3 floats for position)
    );
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);
}
