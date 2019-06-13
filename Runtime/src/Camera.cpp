#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::SetPerspective(float p_near, float p_far, float p_aspect, float p_FOV)
{
	nearPlane = p_near;
	farPlane = p_far;
	aspect = p_aspect;
	FOV = p_FOV;
}

glm::mat4 Camera::GetPerspective()
{
	return 	glm::perspective(FOV, aspect, nearPlane, farPlane);
}

void Camera::SetView(glm::vec3 p_position, glm::vec3 p_target, glm::vec3 p_up)
{
	position = p_position;
	target = p_target;
	up = p_up;
}

glm::mat4 Camera::GetView()
{
	return glm::lookAt(position, target, up);
}

void Camera::MoveForward(float t)
{
	glm::vec3 viewDir = glm::normalize(target - position);

	position += viewDir * t;
	target += viewDir * t;
}

void Camera::MoveRight(float t)
{
	glm::vec3 viewDir = glm::normalize(target - position);
	glm::vec3 rightDir = glm::cross(viewDir, glm::normalize(up));

	position += rightDir * t;
	target += rightDir * t;
}

void Camera::MoveUp(float t)
{
	glm::vec3 viewDir = glm::normalize(target - position);
	glm::vec3 rightDir = glm::cross(viewDir, glm::normalize(up));

	glm::vec3 upDir = glm::cross(viewDir, rightDir);

	position += upDir * t;
	target += upDir * t;
}

void Camera::MouseLook(float right, float up)
{
	glm::quat mouseRotation = glm::quat(glm::radians(glm::vec3(up, -right, 0)));

	// rotate target around position by the mouse inputs
	target = position + (mouseRotation * (target - position));
}
