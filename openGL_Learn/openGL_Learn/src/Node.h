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
#include "camera.h"
#include "model.h"
#include "LightManagere.h"


struct V3F_C3F_T2F
{
	V3F_C3F_T2F()
	{
	}
	V3F_C3F_T2F(glm::vec3 _vertices, glm::vec3 _colors, glm::vec2 _texCoords)
	{
		vertices = _vertices;
		colors = _colors;
		texCoords = _texCoords;

	}
	~V3F_C3F_T2F()
	{
	}

	glm::vec3 vertices;
	glm::vec3 colors;
	glm::vec2 texCoords;
};

class ModelObject;

class Node
{
public:
	Node();
	~Node();

	static Node* create();

	static Node* create(std::string path);

	void init();

	void addChild(Node* child);
	void removeChild(Node* child);

	void setModel(ModelObject* model);
	glm::mat4 getModelMat();

	void setScale(glm::vec3);

	void setPosition(glm::vec3);
	void setRotation(glm::vec3);

	void draw();
private:

	glm::vec3 postion;
	glm::vec3 scale;
	glm::qua<float> rotation;

	std::vector<Node*> children;

	ModelObject* model;

	unsigned int texture;


	Shader* shaderProgram;
};
