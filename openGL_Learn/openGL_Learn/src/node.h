#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"

class Node
{
public:
	Node();
	~Node();

private:

	unsigned int texture;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	Shader* shaderProgram;
};
