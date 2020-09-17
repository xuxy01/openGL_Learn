#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


class Light
{
public:
	Light();
	~Light();
	
	virtual void use(Shader* shader) {};

protected:
	glm::vec3 lightColor;

};

class DirectLight:public Light
{
public:
	DirectLight();
	~DirectLight();
	void use(Shader* shader);
private:
	glm::vec3 direction;
	glm::qua<float> rotation;
};


class PointLight:public Light
{
public:
	PointLight();
	~PointLight();

	void use(Shader* shader);
private:
	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;
};


class SpotLight :public Light
{
public:
	SpotLight();
	~SpotLight();

	void use(Shader* shader);
private:
	glm::vec3 direction;
	glm::vec3 position;
	glm::qua<float> rotation;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

};
