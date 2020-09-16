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
	far(1000.0f),
	speed(10.0f),
	position(glm::vec3(0.0f, 0.0f, 3.0f)),
	rotation(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f))),
	scale(45.0f)
{
}

Camera::~Camera() {}


void Camera::moveLeft(float deltaTime)
{
	float finalSpeed = speed * deltaTime;
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	position += finalSpeed * glm::cross(cameraUp, cameraFront);
}

void Camera::moveRight(float deltaTime)
{

	float finalSpeed = speed * deltaTime;
	printf("moveRight %f 11\n", finalSpeed);
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	position -= finalSpeed * glm::cross(cameraUp, cameraFront);
}
void Camera::moveFront(float deltaTime)
{

	float finalSpeed = speed * deltaTime;
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	position += finalSpeed * cameraFront;
}
void Camera::moveBack(float deltaTime)
{
	float finalSpeed = speed * deltaTime;
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	position -= finalSpeed * cameraFront;
}
//
//float Camera::getMoveSpeed()
//{
//
//	if (lastFrame < 0.0f)
//	{
//		lastFrame = glfwGetTime();
//		return -1;
//	}
//
//	float currentFrame = glfwGetTime();
//	float deltaTime = currentFrame - lastFrame;
//	lastFrame = currentFrame;
//
//	return  deltaTime;
//}


void Camera::moveEnd()
{
}

void Camera::rotate(float x, float y)
{

	float xoffset = x;
	float yoffset = y;

	glm::quat rotationX = glm::qua<float>(glm::radians(glm::vec3(glm::asin(yoffset * 0.1f), glm::asin(xoffset * 0.1f), 0.0f)));

	rotation *= rotationX;
}


void Camera::cameraScale(float yoffset)
{
	printf("cameraScale %f \n", yoffset);
	if (scale >= 1.0f && scale <= 45.0f)
		scale -= yoffset;
	if (scale <= 1.0f)
		scale = 1.0f;
	if (scale >= 45.0f)
		scale = 45.0f;
}


glm::mat4 Camera::getProjection()
{
	return glm::perspective<float>(glm::radians(scale), 800.0 / 600.0, near, far);
	//return glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 1000.0f);
}

glm::mat4 Camera::getView()
{
	glm::vec3 cameraPos = position;
	glm::vec3 cameraFront = rotation * glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}