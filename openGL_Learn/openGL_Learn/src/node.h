#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "lib/std_image.h"

#include "shader.h"


class Node
{
public:
	Node();
	~Node();

	void setTexture(const char* imagePath);
	void clean();
	void init();

	void draw();
private:

	glm::vec3 postion;
	glm::vec3 scale;
	glm::quat ratation;

	unsigned int texture;

	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	Shader* shaderProgram;
};
