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

class Node
{
public:
	Node();
	~Node();

	static Node* create();
	static Node* create(V3F_C3F_T2F* vertices, unsigned int lenght);

	void setTexture(const char* imagePath);
	void clean();
	void init();

	void draw();

	unsigned int getVerticesCount() { return _verticesCount; }

	unsigned int getIndicesCount() { return _indicesCount; }

	V3F_C3F_T2F* getVertices() { return _vertices; }
	GLuint* getIndices() { return _indices; }
private:

	glm::vec3 postion;
	glm::vec3 scale;
	glm::qua<float> rotation;

	Model* model;

	unsigned int texture;

	V3F_C3F_T2F _vertices[16777215];
	GLuint _indices[16777215];
	unsigned int _verticesCount;
	unsigned int _indicesCount;

	Shader* shaderProgram;
};
