#pragma once
#include "Shader.h"
#include "Texture2D.h"
#include "VertexArray.h"
#include <glm/glm.hpp>

class Plane2D
{
public:
    // Constructors
    Plane2D(Shader shader, Texture2D texture);
    Plane2D(Shader shader, Texture2D texture, float x, float y, float z);
    Plane2D(Shader shader, Texture2D texture, float x, float y, float z, float yaw, float pitch, float roll);
    Plane2D(Shader shader, Texture2D texture, float x, float y, float z, float yaw, float pitch, float roll, float length, float width);

    // Setters
    void SetPosition(float x, float y, float z);
    void SetRotation(float yaw, float pitch, float roll);
    void SetSize(float length, float width);
    void SetShader(Shader shader);
    void SetTexture(Texture2D texture);

    // Getters
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;
    glm::vec2 GetSize() const;
    Shader GetShader() const;
    Texture2D GetTexture() const;

    // Methods
    void Draw();
    void OnTick(float deltaTime);

private:
    Shader m_shader;
    Texture2D m_texture;
    VertexArray m_vertexArray;
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec2 m_size;

    void InitializePlane();
};
