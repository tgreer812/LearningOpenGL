#include "Camera.h"
#include <iostream>

Camera::Camera() : Camera(glm::vec3(0.0, 0.0, 0.0)) {}

Camera::Camera(glm::vec3 position)
{
	// figure out how to utilize these world coordinates
	this->m_position = position;
	this->m_fov = glm::radians(60.0f);
	this->m_viewDistance = -3.0f;

	_calculateModelMatrix();
	_calculateViewMatrix();
	_calculateProjectionMatrix();
}

void Camera::Move(glm::vec3 translation) {
	this->m_position += translation;
	std::cout << "Camera position: " << this->m_position.x << ", " << this->m_position.y << ", " << this->m_position.z << std::endl;

}

void Camera::SetAspectRatio(float aspectRatio) {
	this->m_aspectRatio = aspectRatio;
}

void Camera::SetViewDistance(float viewDistance) {
	this->m_viewDistance;
}

glm::mat4 Camera::GetModelMatrix() {
	_calculateModelMatrix();
	return this->m_modelMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
	_calculateViewMatrix();
	return this->m_viewMatrix;
}

glm::mat4 Camera::GetProjectionMatrix() {
	_calculateProjectionMatrix();
	return this->m_projectionMatrix;
}

void Camera::_calculateModelMatrix() {
	// I believe here is where we need to translate/rotate the model matrix based on camera position?
	glm::mat4 model_matrix = glm::mat4(1.0f);
	constexpr float model_rotation = glm::radians(-55.0f);

	// wherever the camera is positioned in the world relative to the origin needs to be negated
	// so that we can translate every other object in the opposite direction
	this->m_modelMatrix = glm::translate(model_matrix, -1.0f * this->m_position);

	// hardcoding rotation for now, but this should get pulled from the camera attributes as well
	this->m_modelMatrix = glm::rotate(model_matrix, model_rotation, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Camera::_calculateViewMatrix() {
	glm::mat4 view_matrix = glm::mat4(1.0f);
	this->m_viewMatrix = glm::translate(view_matrix, glm::vec3(0.0f, 0.0f, this->m_viewDistance));
}

void Camera::_calculateProjectionMatrix() {
	this->m_projectionMatrix = glm::perspective(
		this->m_fov,
		this->m_aspectRatio,
		0.1f,					// todo: extract these last two fields as 'settable' camera attributes
		100.0f
	);
}