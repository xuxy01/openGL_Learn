#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Light
{
public:
	Light();
	~Light();

private:
	glm::vec3 postion;
	glm::vec3 scale;
	glm::qua<float> rotation;

};

class DirectLight:Light
{
public:
	DirectLight();
	~DirectLight();
	virtual float getLight();
private:

};

DirectLight::DirectLight()
{
}

DirectLight::~DirectLight()
{
}

class PointLight:Light
{
public:
	PointLight();
	~PointLight();

private:

};

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}

class Spotlight:Light
{
public:
	Spotlight();
	~Spotlight();

private:

};

Spotlight::Spotlight()
{
}

Spotlight::~Spotlight()
{
}