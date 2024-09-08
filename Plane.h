#pragma once
#include "VertexArray.h"
#include <glm/glm.hpp>

class Plane
{
public:
    // Constructors
    Plane();
    Plane(float x, float y, float z);
    Plane(float x, float y, float z, float yaw, float pitch, float roll);
    Plane(float x, float y, float z, float yaw, float pitch, float roll, float length, float width);

    // Setters
    void SetPosition(float x, float y, float z);
    void SetRotation(float yaw, float pitch, float roll);
    void SetSize(float length, float width);

    // Getters
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec2 GetSize() const;

    // Returns the vertex array object (VAO) that external code can use to render
    std::vector<float> GetVertexPositions() const;
    std::vector<unsigned int> GetIndices() const;

    glm::mat4 GetModelMatrix() const;

private:
    VertexArray m_vertexArray;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec2 m_size;
};
