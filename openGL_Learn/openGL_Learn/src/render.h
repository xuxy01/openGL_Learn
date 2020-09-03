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

	void fillVertexData();
	
private:

	V3F_C3F_T2F _vertices[65535];
	GLuint _indices[65535];
	GLushort _triBatchesToDraw[65535];
	unsigned int _verticesCount;
	unsigned int _indicesCount;

	GLuint _vao;
	GLuint _vbo;
	GLuint _ebo;

	std::list<Node*> nodes;
};
