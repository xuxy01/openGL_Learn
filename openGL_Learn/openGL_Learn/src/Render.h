#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list> 

#include "lib/std_image.h"

#include "shader.h"
#include "node.h"

class Node;

class Render
{
public:
	Render();
	~Render();
	static Render* getInstance();

	void init();
	void addNode(Node* node);
	void draw();
	void createFrameBuffer();
	void createScreenVAO();
	void renderScreen();

private:

	unsigned int quadVAO, quadVBO;
	unsigned int fbo;
	unsigned int textureColorbuffer;

	std::vector<Node*> nodes;
};
