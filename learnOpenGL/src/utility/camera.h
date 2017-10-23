#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum cameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED       = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

class Camera
{
private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_worldUp;
	glm::vec3 m_up;
	glm::vec3 m_right;

	float m_yaw;
	float m_pitch;

	float m_movementSpeed;
	float m_mouseSensitivity;
	float m_zoom;

public:
	//yaw rotate with y axis, pitch ratate with x axis
	Camera(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& front = glm::vec3(0.0f, 0.0f, -1.0f) , const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

	inline float getZoom() const { return m_zoom; }
	inline const glm::vec3& getPosition() const { return m_position; }
	inline glm::mat4 getViewMatrix() const { return glm::lookAt(m_position, m_position + m_front, m_up); }
	
	void processKeyboard(cameraMovement direction, float deltaTime);
	void processMouseMovement(float xOffset, float yOffset);
	void processMouseScroll(float yOffset);
private:
	void updateCameraVector();
};