#include "Light.h"


Light::Light()
	:lightColor(glm::vec3(1.0f,1.0f,1.0f))
{
}

Light::~Light()
{
}

DirectLight::DirectLight()
	:direction(glm::vec3(-1.0f, 0.0f, 0.0f)),
	rotation(glm::quat(glm::radians(glm::vec3(0.0f, 0.0, 0.0f))))
{
	
}

DirectLight::~DirectLight()
{
}

void DirectLight::use(Shader* shader)
{	
	//rotation = rotation * glm::quat(glm::radians(glm::vec3(0.0f, 0.05f, 0.0f)));
	glm::vec3 newDirection = rotation * direction;
	shader->setFloat3("directLight.direction", newDirection.x, newDirection.y, newDirection.z);
	shader->setFloat3("directLight.lightColor", lightColor.x, lightColor.y, lightColor.z);
}

PointLight::PointLight()
	:position(glm::vec3(0.0f, 0.0f, 0.5f)),
	constant(1.0f),
	linear(0.045f),
	quadratic(0.0075f)
{
}

PointLight::~PointLight()
{
}
void PointLight::use(Shader* shader)
{
	//position = glm::quat(glm::radians(glm::vec3(0.0f, 0.02f, 0.0f))) * position;
	shader->setFloat3("pointLight.position", position.x, position.y, position.z);
	shader->setFloat("pointLight.constant", constant);
	shader->setFloat("pointLight.linear", linear);
	shader->setFloat("pointLight.quadratic", quadratic);

	shader->setFloat3("pointLight.lightColor", lightColor.x, lightColor.y, lightColor.z);
}


SpotLight::SpotLight()
	:position(glm::vec3(0.0f, 0.0f, 1.0f)),
	rotation(glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)))),
	direction(glm::vec3(0.0f, 0.0f, -1.0f)),
	constant(1.0f),
	linear(0.045f),
	quadratic(0.0075f),
	cutOff(0.91f),
	outerCutOff(0.82f)
{
}

SpotLight::~SpotLight()
{
}
void SpotLight::use(Shader* shader)
{
	//rotation = rotation * glm::quat(glm::radians(glm::vec3(0.0f, 0.02f, 0.0f)));
	glm::vec3 newDirection = rotation * direction;

	shader->setFloat3("spotLight.direction", newDirection.x, newDirection.y, newDirection.z);
	shader->setFloat3("spotLight.position", position.x, position.y, position.z);
	shader->setFloat("spotLight.cutOff", cutOff);
	shader->setFloat("spotLight.outerCutOff", outerCutOff);
	shader->setFloat("spotLight.constant", constant);
	shader->setFloat("spotLight.linear", linear);
	shader->setFloat("spotLight.quadratic", quadratic);
	shader->setFloat3("spotLight.lightColor", lightColor.x, lightColor.y, lightColor.z);
}