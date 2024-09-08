#include "Plane2D.h"
#include <glm/gtc/matrix_transform.hpp>

// Define the plane vertices and indices using std::vector
static const std::vector<float> plane_vertices = {
    // positions
    0.5f,  0.5f, 0.0f,  // top right
    0.5f, -0.5f, 0.0f,  // bottom right
   -0.5f, -0.5f, 0.0f,  // bottom left
   -0.5f,  0.5f, 0.0f,  // top left
};

static const std::vector<unsigned int> indices = {
    0, 1, 2,  // Triangle 1
    0, 2, 3   // Triangle 2
};

// Constructors
Plane2D::Plane2D(Shader shader, Texture2D texture)
    : m_shader(shader), m_texture(texture), m_position(0.0f, 0.0f, 0.0f), m_rotation(0.0f, 0.0f, 0.0f), m_size(1.0f, 1.0f) {
    InitializePlane();
}

Plane2D::Plane2D(Shader shader, Texture2D texture, float x, float y, float z)
    : m_shader(shader), m_texture(texture), m_position(x, y, z), m_rotation(0.0f, 0.0f, 0.0f), m_size(1.0f, 1.0f) {
    InitializePlane();
}

Plane2D::Plane2D(Shader shader, Texture2D texture, float x, float y, float z, float yaw, float pitch, float roll)
    : m_shader(shader), m_texture(texture), m_position(x, y, z), m_rotation(yaw, pitch, roll), m_size(1.0f, 1.0f) {
    InitializePlane();
}

Plane2D::Plane2D(Shader shader, Texture2D texture, float x, float y, float z, float yaw, float pitch, float roll, float length, float width)
    : m_shader(shader), m_texture(texture), m_position(x, y, z), m_rotation(yaw, pitch, roll), m_size(length, width) {
    InitializePlane();
}

// Initialize the plane
void Plane2D::InitializePlane() {
    // Create the vertex array using std::vector<float> and std::vector<unsigned int>
    m_vertexArray = VertexArray(plane_vertices, indices);
}

// Setters
void Plane2D::SetPosition(float x, float y, float z) {
    m_position = glm::vec3(x, y, z);
}

void Plane2D::SetRotation(float yaw, float pitch, float roll) {
    m_rotation = glm::vec3(yaw, pitch, roll);
}

void Plane2D::SetSize(float length, float width) {
    m_size = glm::vec2(length, width);
}

void Plane2D::SetShader(Shader shader) {
    m_shader = shader;
}

void Plane2D::SetTexture(Texture2D texture) {
    m_texture = texture;
}

// Getters
glm::vec3 Plane2D::GetPosition() const {
    return m_position;
}

glm::vec3 Plane2D::GetRotation() const {
    return m_rotation;
}

glm::vec2 Plane2D::GetSize() const {
    return m_size;
}

Shader Plane2D::GetShader() const {
    return m_shader;
}

Texture2D Plane2D::GetTexture() const {
    return m_texture;
}

// Draw the plane
void Plane2D::Draw() {
    //// Use the shader program
    //m_shader.Use();

    //// Set up the model matrix based on position, rotation, and size
    ///*
    //glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, m_position);

    //// Apply a visible rotation around the x-axis and y-axis
    //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate 45 degrees around x-axis
    //model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));  // Rotate 30 degrees around y-axis

    //// Apply any additional rotations based on the object's rotation attributes
    //model = glm::rotate(model, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    //model = glm::rotate(model, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    //model = glm::scale(model, glm::vec3(m_size, 1.0f)); // Scale only in X and Y
    //*/

    //// Hardcoded model matrix for debugging
    //glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));  // Translate the object
    //model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));  // Rotate around the x-axis

    //// Set the model, view, and projection matrices in the shader
    //m_shader.setMatrix4("modelMatrix", model);
    //m_shader.setMatrix4("viewMatrix", viewMat);
    //m_shader.setMatrix4("projectionMatrix", projMat);

    //// Bind the texture
    //m_texture.Bind();
    //m_shader.setInt("ourTexture", 0); // 0 corresponds to GL_TEXTURE0

    //// Bind the vertex array and draw the plane
    //m_vertexArray.Use();
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


// OnTick method
void Plane2D::OnTick(float deltaTime) {
    // Implement any per-frame logic for the plane here
}
