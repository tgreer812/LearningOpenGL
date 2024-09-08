#include "Camera.h"
#include <iostream>

Camera::Camera() : Camera(glm::vec3(0.0f, 0.0f, -3.0f)) {}

Camera::Camera(glm::vec3 position)
{
	this->m_position = position;
	this->m_fov = glm::radians(60.0f);
	this->m_viewDistance = -3.0f;
	this->m_lookSensitivity = 0.01f;

	// Have the camera 'look towards' the origin of the world
	this->m_targetPoint = glm::vec3(0.0f, 0.0f, 0.0f);

	// The direction vector represents where the camera is looking. We can
	// calculate this by subtracting the vector representing the camera's current position
	// from the 'point' it's looking at
	this->m_cameraDirection = glm::normalize(m_targetPoint - m_position);

	// camera starts 'flat' so the up vector just points towards positive y
	// so we can initialize it (0.0f, 1.0f, 0.0f)
	this->m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	// The right vector is the cross product of the up vector and the direction vector
	this->m_cameraRight = glm::normalize(glm::cross(this->m_cameraUp, this->m_cameraDirection));

	this->m_lookAt = glm::lookAt(this->m_position, this->m_targetPoint, this->m_cameraUp);
	
	//_calculateModelMatrix();
	_calculateViewMatrix();
	_calculateProjectionMatrix();
}

// TODO: it's possible over time the floats will drift because of fp inaccuracy from what I've read
// if that starts to happen try normalizing/rounding them back to fix it
void Camera::Move(glm::vec3 translation, float deltaTime) {
	// Move forward/backward (along the camera's direction) and left/right (along the camera's right vector)
	this->m_position -= translation.x * this->m_cameraRight * this->m_cameraSpeed * deltaTime; // Strafe left/right
	this->m_position += translation.z * this->m_cameraDirection * this->m_cameraSpeed * deltaTime; // Move forward/backward

	// Recalculate the target point based on the new position
	this->m_targetPoint = this->m_position + this->m_cameraDirection;

	// Update the LookAt matrix
	this->m_lookAt = glm::lookAt(this->m_position, this->m_targetPoint, this->m_cameraUp);

	std::cout << "Camera position: " << this->m_position.x << ", " << this->m_position.y << ", " << this->m_position.z << std::endl;
}


void Camera::Rotate(float xoffset, float yoffset) {
	this->m_yaw += xoffset * this->m_lookSensitivity;
	this->m_pitch += yoffset * this->m_lookSensitivity;

	if (m_pitch > 89.0f) { m_pitch = 89.0f; }
	if (m_pitch < -89.0f) { m_pitch = -89.0f; }

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = -sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	this->m_cameraDirection = glm::normalize(direction);

	// recalculate target point
	this->m_cameraRight = glm::normalize(glm::cross(this->m_cameraDirection, this->m_cameraUp));
	this->m_targetPoint = this->m_position + this->m_cameraDirection;
	this->m_lookAt = glm::lookAt(this->m_position, this->m_targetPoint, this->m_cameraUp);
}

void Camera::SetAspectRatio(float aspectRatio) {
	this->m_aspectRatio = aspectRatio;
}

void Camera::SetViewDistance(float viewDistance) {
	this->m_viewDistance;
}

//glm::mat4 Camera::GetModelMatrix() {
//	_calculateModelMatrix();
//	return this->m_modelMatrix;
//}

glm::mat4 Camera::GetViewMatrix() {
	_calculateViewMatrix();
	return this->m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() {
	_calculateProjectionMatrix();
	return this->m_projectionMatrix;
}

//void Camera::_calculateModelMatrix() {
//	// I believe here is where we need to translate/rotate the model matrix based on camera position?
//	glm::mat4 model_matrix = glm::mat4(1.0f);
//	constexpr float model_rotation = glm::radians(0.0f);
//
//	// hardcoding rotation for now, but this should get pulled from the camera attributes as well
//	this->m_modelMatrix = glm::rotate(model_matrix, model_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
//}

void Camera::_calculateViewMatrix() {
	this->m_viewMatrix = this->m_lookAt;
}

void Camera::_calculateProjectionMatrix() {
	this->m_projectionMatrix = glm::perspective(
		this->m_fov,
		this->m_aspectRatio,
		0.1f,					// todo: extract these last two fields as 'settable' camera attributes
		100.0f
	);
}