#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list> 

#include "lib/std_image.h"

#include "shader.h"
#include "node.h"

class Camera
{
public:
	Camera();
	~Camera();

	static Camera* getInstance();

	glm::mat4 getProjection();
	glm::mat4 getView();

	void moveLeft();
	void moveRight();
	void moveFront();
	void moveBack();
	void moveEnd();
	float getMoveSpeed();

	void rotate(float x, float y);


	void cameraScale(float scale);

private :
	//Node* target;

	float angle;
	float near;
	float far;

	float speed;
	float lastFrame; // 上一帧的时间

	glm::vec3 position;
	glm::quat rotation;
	float scale;

	bool firstMouse;
	float lastX;
	float lastY;

};