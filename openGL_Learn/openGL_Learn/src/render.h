#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Render
{
public:
	Render();
	~Render();

	static Render* getInstance();

	void init();
	void draw();
	void clean();
	
private:

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int shaderProgram;

};
