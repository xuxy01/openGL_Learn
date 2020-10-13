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
	void createSkyBoxVAO();
	void renderScreen();
	void renderSkyBox();
	void createCameraUBO();

	const unsigned int getSkyBoxTexture();

private:

	unsigned int quadVAO, quadVBO;
	unsigned int skyBoxVAO, skyBoxVBO;
	unsigned int fbo;
	unsigned int textureColorbuffer;
	unsigned int cubemapTexture;
	unsigned int cameraUBO;

	std::vector<Node*> nodes;
};
