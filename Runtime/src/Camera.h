#ifndef __CAMERA_H_
#define __CAMERA_H_
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Camera
{
public:
	Camera();
	~Camera();
	void SetPerspective(float p_near, float p_far, float p_aspect, float p_FOV);
	glm::mat4 GetPerspective();

	void SetView(glm::vec3 p_position, glm::vec3 p_target, glm::vec3 p_up);
	glm::mat4 GetView();

	void MoveForward(float t);
	void MoveRight(float t);
	void MoveUp(float t);

	void MouseLook(float up, float right);

private:
	float nearPlane;
	float farPlane;
	float FOV;
	float aspect;

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
};

#endif // __CAMERA_H_