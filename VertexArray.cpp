#include "VertexArray.h"

VertexArray::VertexArray(const float vertices[], size_t vertexCount, const unsigned int indices[], size_t indexCount) {
    // No need for new, std::vector manages memory
    this->_vertices = std::vector<float>(vertices, vertices + vertexCount);
    this->_indices = std::vector<unsigned int>(indices, indices + indexCount);
}

VertexArray::~VertexArray() {
    // No need for delete, std::vector automatically handles memory cleanup
}

void VertexArray::Use() {
	GLuint VAO, VBO, EBO;

	// Generate buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind vertex array object
	glBindVertexArray(VAO);

	// Bind and copy the vertices into the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(
		GL_ARRAY_BUFFER,
		this->_vertices.size() * sizeof(float),  // Correct size in bytes
		this->_vertices.data(),
		GL_STATIC_DRAW
	);

	// Bind the EBO and copy the indices into it
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		this->_indices.size() * sizeof(unsigned int),  // Correct size in bytes
		this->_indices.data(),
		GL_STATIC_DRAW
	);

	// Now set the vertex attribute pointers
	// Position attribute
	glVertexAttribPointer(
		0,                   // Attribute index 0 corresponds to position
		3,                   // Size (3 components per vertex)
		GL_FLOAT,            // Type (float)
		GL_FALSE,            // Don't normalize
		6 * sizeof(float),   // Stride (each vertex has 6 floats: 3 for position, 3 for color)
		(void*)0             // Offset to the first component (position starts at 0)
	);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(
		1,                               // Attribute index 1 corresponds to color
		3,                               // Size (3 components per vertex)
		GL_FLOAT,                        // Type (float)
		GL_FALSE,                        // Don't normalize
		6 * sizeof(float),               // Stride (each vertex has 6 floats)
		(void*)(3 * sizeof(float))       // Offset (color starts after the first 3 floats for position)
	);
	glEnableVertexAttribArray(1);
}

