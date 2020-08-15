#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lib/std_image.h"

#include "shader.h"


class Render
{
public:
	Render();
	~Render();

	static Render* getInstance();

	void init();
	void draw();
	void clean();

	void setTexture(const char* imagePath);
	
private:

	unsigned int texture;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	Shader* shaderProgram;
};
