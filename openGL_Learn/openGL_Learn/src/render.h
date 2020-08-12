#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Render
{
public:
	Render();
	~Render();

	static Render* getInstance();

	void draw();
	
private:

};
