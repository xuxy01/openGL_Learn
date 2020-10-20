#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "Light.h"

class Light;
class DirctLight;
class SpotLight;
class PointLight;

class LightManager
{
public:
	LightManager();
	~LightManager();

	static LightManager* getInstance();

	Light* getLight(int index);

	void addLight(Light*);

	void use(Shader* shader);
private:
	std::vector<Light*> lights;
};