#include "camera.h"


static Camera* _instance = nullptr;

Camera* Camera::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) Camera();

	}

	return _instance;
}


Camera::Camera():
	//target(nullptr),
	angle(45.0f),
	near(0.1f),
	far(100.0f),
	speed(2.5f),
	lastFrame(-1),
	firstMouse(true),
	lastX(0.0f),
	lastY(0.0f),
	position(glm::vec3(0.0f, 0.0f, -1.0f)),
	rotation(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f))),
	scale(45.0f)
{
}

Camera::~Camera() {}


void Camera::moveLeft()
{
	if (getMoveSpeed() < 0) return;

	float finalSpeed = speed * getMoveSpeed();
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	position += finalSpeed * glm::cross(cameraUp, cameraFront);
}

void Camera::moveRight() 
{
	if (getMoveSpeed() < 0) return;

	float finalSpeed = speed * getMoveSpeed();
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	position -= finalSpeed * glm::cross(cameraUp, cameraFront);
}
void Camera::moveFront()
{
	if (getMoveSpeed() < 0) return;

	float finalSpeed = speed * getMoveSpeed();
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	position += finalSpeed * cameraFront;
}
void Camera::moveBack()
{
	if (getMoveSpeed() < 0) return;

	float finalSpeed = speed * getMoveSpeed();
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	position -= finalSpeed * cameraFront;
}

float Camera::getMoveSpeed()
{

	if (lastFrame < 0.0f)
	{
		lastFrame = glfwGetTime();
		return -1;
	}

	float currentFrame = glfwGetTime();
	float deltaTime = currentFrame - lastFrame;

	return  deltaTime;
}


void Camera::moveEnd()
{
	lastFrame = -1;
}

void Camera::rotate(float x, float y)
{
	//if (firstMouse)
	//{
	//	lastX = x;
	//	lastY = y;
	//	firstMouse = false;
	//}
	//float sensitivity = 0.05f;
	//float xOffset = x - lastX;
	//float yOffset = y - lastY;

	//
	//glm::quat rotationX = glm::qua<float>(glm::asin(xOffset * sensitivity), 0.0f, 1.0f, 0.0f);
	//glm::quat rotationY = glm::qua<float>(glm::asin(yOffset * sensitivity), -1.0f, 0.0f, 0.0f);

	//rotation *= (rotationX * rotationY);
}


void Camera::cameraScale(float scale)
{
	if (scale >= 1.0f && scale <= 45.0f)
		scale -= scale;
	if (scale <= 1.0f)
		scale = 1.0f;
	if (scale >= 45.0f)
		scale = 45.0f;
}


glm::mat4 Camera::getProjection()
{
	return glm::perspective<float>(glm::radians(45.0), 800 / 600, near, far);
}

glm::mat4 Camera::getView()
{
	glm::vec3 cameraPos = position;
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}