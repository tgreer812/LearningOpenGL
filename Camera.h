#pragma once
#include "glm/glm.hpp"
#include "glm/ext.hpp"

// TODO: Separate the glm code out such that only the implementation utilizes it
// and the interface only requires floats. just doing this to get the math working
class Camera
{
public:
	Camera();
	Camera(glm::vec3 position);
	Camera(glm::vec3 position, glm::vec3 orientation);

	void Move(glm::vec3 translation);
	void Rotate(glm::vec3 rotation);
	void SetAspectRatio(float aspectRatio);
	void SetViewDistance(float viewDistance);

	glm::mat4 GetModelMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 m_position;
	//glm::vec3 m_orientation;

private:
	float m_fov;
	float m_viewDistance;
	float m_aspectRatio = 1.0f;
	float m_scalingFactor = 0.1f;

	glm::vec3 m_targetPoint;
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;

	glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	void _calculateModelMatrix();
	void _calculateViewMatrix();
	void _calculateProjectionMatrix();
};

