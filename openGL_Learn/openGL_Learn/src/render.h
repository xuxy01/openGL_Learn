#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list> 

#include "lib/std_image.h"

#include "shader.h"
#include "node.h"


class Render
{
public:
	Render();
	~Render();

	static Render* getInstance();

	void init();
	void draw();
	
private:

	std::list<Node> nodes;
};
