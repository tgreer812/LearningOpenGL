#include "VertexArray.h"
#include <iostream>

// This shit is fucked

#define CHECK_GL_ERROR() {                                      \
    GLenum err;                                                 \
    while((err = glGetError()) != GL_NO_ERROR) {                \
        std::cerr << "OpenGL error: " << err                    \
                  << " in file " << __FILE__                    \
                  << " at line " << __LINE__ << std::endl;      \
    }                                                           \
}

// Default constructor
VertexArray::VertexArray()
    : VAO(0), VBO(0), EBO(0), dataBuffered(false) {
}

// Constructor with data
VertexArray::VertexArray(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : m_vertices(vertices), m_indices(indices), VAO(0), VBO(0), EBO(0), dataBuffered(false) {
    // Generate VAO, VBO, and EBO and buffer data immediately
    BufferData();
}

// Allow moving of VertexArray
VertexArray::VertexArray(VertexArray&& other) noexcept {
    // If this VertexArray was already being used then free its underlying vertex array
    if (VAO != 0) { glDeleteVertexArrays(1, &this->VAO); }
    if (VBO != 0) { glDeleteBuffers(1, &VBO); }
    if (EBO != 0) { glDeleteBuffers(1, &EBO); }

    // Now make it take control of the other vertex array
    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;
    m_vertices = std::move(other.m_vertices);
    m_indices = std::move(other.m_indices);

    other.VAO = 0;
    other.VBO = 0; 
    other.EBO = 0;

    other.m_vertices.clear();
    other.m_indices.clear();
}

VertexArray& VertexArray::operator=(VertexArray&& other) noexcept {
    if (this != &other) {
        // Free the current VAO, VBO, and EBO to avoid resource leaks
        if (VAO != 0) {
            glDeleteVertexArrays(1, &VAO);
        }
        if (VBO != 0) {
            glDeleteBuffers(1, &VBO);
        }
        if (EBO != 0) {
            glDeleteBuffers(1, &EBO);
        }

        // Transfer ownership of resources
        VAO = other.VAO;
        VBO = other.VBO;
        EBO = other.EBO;
        m_vertices = std::move(other.m_vertices);
        m_indices = std::move(other.m_indices);

        // Reset the other object to a valid but empty state
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
        other.m_vertices.clear();
        other.m_indices.clear();
    }
    return *this;
}

// Destructor
VertexArray::~VertexArray() {
    Clear();  // Cleanup OpenGL buffers
}

// Get the size of the indices (for draw calls)
unsigned int VertexArray::GetSize() const {
    return static_cast<unsigned int>(m_indices.size());
}

// Bind and use the vertex array
void VertexArray::Bind() {
    if (!dataBuffered) {
        BufferData();  // If data hasn't been buffered yet, buffer it now
    }

    glBindVertexArray(VAO);  // Bind the VAO for use
    CHECK_GL_ERROR();  // Check for errors after binding the VAO
}

void VertexArray::Unbind() {
    GLint currentlyBoundVAO = 0;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentlyBoundVAO);

    if (currentlyBoundVAO == VAO)
    {
        glBindVertexArray(0);
    }
    else {
        std::cout << "WARNING: Attempted to bind a VertexArray that is not bound!" << std::endl;
    }
}

// Update the vertex and index data, and re-buffer it
void VertexArray::UpdateData(const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    m_vertices = vertices;
    m_indices = indices;
    BufferData();  // Re-buffer the data when updated
}

// Clear out the buffers and reset flags
void VertexArray::Clear() {
    // Delete OpenGL buffers
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
    if (EBO) glDeleteBuffers(1, &EBO);

    VAO = 0;
    VBO = 0;
    EBO = 0;
    dataBuffered = false;  // Reset the buffered flag
    CHECK_GL_ERROR();  // Check for errors after deleting buffers

    this->m_vertices.clear();
    this->m_indices.clear();
}

// Internal method to buffer vertex and index data to GPU
void VertexArray::BufferData() {
    if (!VAO) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        CHECK_GL_ERROR();  // Check for errors after generating buffers
    }

    glBindVertexArray(VAO);
    CHECK_GL_ERROR();  // Check for errors after binding VAO

    // Buffer vertex data into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    CHECK_GL_ERROR();  // Check for errors after binding VBO

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
    CHECK_GL_ERROR();  // Check for errors after buffering vertex data

    // Buffer index data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    CHECK_GL_ERROR();  // Check for errors after binding EBO

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    CHECK_GL_ERROR();  // Check for errors after buffering index data

    // Set vertex attribute pointers
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    CHECK_GL_ERROR();  // Check for errors after setting the position attribute

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    CHECK_GL_ERROR();  // Check for errors after setting the color attribute

    // Texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    CHECK_GL_ERROR();  // Check for errors after setting the texture attribute

    glBindVertexArray(0);  // Unbind VAO after setup
    CHECK_GL_ERROR();  // Check for errors after unbinding VAO

    dataBuffered = true;  // Set the buffered flag to true
}
