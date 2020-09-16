#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

class LightManager
{
public:
	LightManager();
	~LightManager();

	static LightManager* getInstance();
};