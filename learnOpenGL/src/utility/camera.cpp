#include "camera.h"

Camera::Camera(const glm::vec3& position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/, const glm::vec3& front /*= glm::vec3(0.0f, 0.0f, -1.0f) */, const glm::vec3& up /*= glm::vec3(0.0f, 1.0f, 0.0f)*/, float yaw /*= YAW*/, float pitch /*= PITCH*/)
	: m_position(position), m_front(front), m_worldUp(up), m_yaw(yaw), m_pitch(pitch), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
	updateCameraVector();
}

void Camera::processKeyboard(cameraMovement direction, float deltaTime)
{
	float cameraSpeed = m_movementSpeed * deltaTime;
	if (direction == FORWARD)
	{
		m_position += cameraSpeed * m_front;
	}
	if (direction == BACKWARD)
	{
		m_position -= cameraSpeed * m_front;
	}
	if (direction == LEFT)
	{
		m_position -= cameraSpeed * m_right;
	}
	if (direction == RIGHT)
	{
		m_position += cameraSpeed * m_right;
	}

	//look around while staying on the xz plane; a real FPS camera
	//m_position.y = 0.0f; 
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	if (m_pitch > 89.0f)
	{	
		m_pitch = 89.0f;
	}	
	if (m_pitch < -89.0f)
	{	
		m_pitch = -89.0f;
	}

	updateCameraVector();
}

void Camera::processMouseScroll(float yOffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
	{
		m_zoom -= yOffset;
	}
	if (m_zoom <= 1.0f)
	{
		m_zoom = 1.0f;
	}
	if (m_zoom >= 45.0f)
	{
		m_zoom = 45.0f;
	}
}

void Camera::updateCameraVector()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	front.y = sin(glm::radians(m_pitch));
	front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	m_front = glm::normalize(front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
