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

	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void moveFront(float deltaTime);
	void moveBack(float deltaTime);
	void moveEnd();
	//float getMoveSpeed();

	void rotate(float x, float y);

	void update();
	void cameraScale(float scale);

	glm::vec3 getPosition();

private :
	//Node* target;

	float angle;
	float near;
	float far;

	float speed;

	glm::vec3 position;
	glm::quat rotation;
	float scale;


};