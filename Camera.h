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

	void Move(glm::vec3 translation, float deltaTime);
	void Rotate(float xoffset, float yoffset);
	void SetAspectRatio(float aspectRatio);
	void SetViewDistance(float viewDistance);

	bool Enabled() { return this->m_cameraEnabled; }
	void Enable() { this->m_cameraEnabled = true; }
	void Disable() { this->m_cameraEnabled = false; }

	//glm::mat4 GetModelMatrix();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	glm::vec3 m_position;

private:
	float m_fov;
	float m_viewDistance;
	float m_aspectRatio = 1.0f;
	float m_cameraSpeed = 5.0f;
	float m_lookSensitivity;

	float m_yaw = 0.01f;		// yaw is the degrees of rotation about the y axis 
							//		(if it were an airplane, think about how much it's turning on the sides)
	float m_pitch = 0.0f;	// pitch is the degrees of rotation about the x axis

	//float m_roll;	// not implemented

	bool m_cameraEnabled = true;

	glm::vec3 m_targetPoint;
	glm::vec3 m_cameraDirection;
	glm::vec3 m_cameraUp;
	glm::vec3 m_cameraRight;
	glm::mat4 m_lookAt;

	//glm::mat4 m_modelMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	//void _calculateModelMatrix();
	void _calculateViewMatrix();
	void _calculateProjectionMatrix();
};

