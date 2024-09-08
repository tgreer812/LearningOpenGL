#include "Plane.h"
#include <glm/ext.hpp >

Plane::Plane() : Plane(0.0f, 0.0f, 0.0f) {}
Plane::Plane(float x, float y, float z) : Plane(x, y, z, 0.0f, 0.0f, 0.0f) {}
Plane::Plane(float x, float y, float z, float yaw, float pitch, float roll) : Plane(x, y, z, yaw, pitch, roll, 100, 100) {}


Plane::Plane(float x, float y, float z, float yaw, float pitch, float roll, float length, float width) {
	this->m_position = glm::vec3(x, y, z);
	this->m_rotation = glm::vec3(yaw, pitch, roll);
	this->m_size = glm::vec2(length, width);
}

// Setters
void Plane::SetPosition(float x, float y, float z) { this->m_position = glm::vec3(x, y, z); }
void Plane::SetRotation(float yaw, float pitch, float roll) { this->m_rotation = glm::vec3(yaw, pitch, roll); }
void Plane::SetSize(float length, float width) { this->m_size = glm::vec2(length, width); }

// Getters
glm::vec3 Plane::GetPosition() const { return this->m_position; }
glm::vec3 Plane::GetRotation() const { return this->m_rotation; }
glm::vec2 Plane::GetSize() const { return this->m_size; }

// Return only vertex positions in local coordinates
std::vector<float> Plane::GetVertexPositions() const {
    // Local space coordinates for the plane (centered around origin)
    return {
        -1.0f, -1.0f, 0.0f,  // Bottom-left
         1.0f, -1.0f, 0.0f,  // Bottom-right
         1.0f,  1.0f, 0.0f,  // Top-right
        -1.0f,  1.0f, 0.0f   // Top-left
    };
}

// Optionally, return indices for indexed drawing
std::vector<unsigned int> Plane::GetIndices() const {
    return {
        0, 2, 3,  // First triangle
        0, 1, 2   // Second triangle
    };
}

glm::mat4 Plane::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);  // Initialize as identity matrix

    // Apply translation
    model = glm::translate(model, m_position);

    // Apply rotation (in radians)
    model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Pitch (X-axis)
    model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Yaw (Y-axis)
    model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Roll (Z-axis)

    // Apply scaling (adjust size)
    model = glm::scale(model, glm::vec3(m_size.x, m_size.y, 1.0f));  // Plane is 2D, so scale in X and Y

    return model;

}