#include "render.h"

#include <iostream>


GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

static Render* _instance = nullptr;

Render* Render::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) Render();

	}

	return _instance;
}


Render::Render()
{
	//init();
}

Render::~Render()
{
}


void Render::init()
{
	std::cout << "init" << std::endl;
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	/*glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C3F_T2F), (void*)offsetof(V3F_C3F_T2F, vertices));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(V3F_C3F_T2F), (void*)offsetof(V3F_C3F_T2F, colors));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(V3F_C3F_T2F), (void*)offsetof(V3F_C3F_T2F, texCoords));
	glEnableVertexAttribArray(2);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	nodes.push_back(Node::create());


	V3F_C3F_T2F vertices[] = {
		V3F_C3F_T2F(glm::vec3(1.5f, 1.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)),
		V3F_C3F_T2F(glm::vec3(1.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)),
		V3F_C3F_T2F(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		V3F_C3F_T2F(glm::vec3(0.5f, 1.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f))
	};

	nodes.push_back(Node::create(vertices, 4));
}


void Render::fillVertexData()
{
	_verticesCount = 0;
	_indicesCount = 0;

	std::list<Node*>::iterator i;
	int count = 0;
	for (i = nodes.begin(); i != nodes.end(); i++)
	{
		Node* node = (*i);
		memcpy(&_vertices[_verticesCount], node->getVertices(), sizeof(V3F_C3F_T2F) * node->getVerticesCount());

		for (int j = 0; j < node->getIndicesCount(); j++)
		{
			GLuint* indices = node->getIndices();

			_indices[_indicesCount + j] = _verticesCount + indices[j];
		}

		_triBatchesToDraw[count] = _indicesCount;

		_verticesCount += node->getVerticesCount();
		_indicesCount += node->getIndicesCount();

		count += 1;
	}
}

#define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))
//
//void Render::draw()
//{
//
//	fillVertexData();
//
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST);
//
//
//	glBindVertexArray(_vao);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices[0])*_verticesCount, _vertices, GL_STATIC_DRAW);
//
//	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	//std::cout << "Render::draw  _indicesCount= " << _indicesCount << std::endl;
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices[0])* _indicesCount, _indices, GL_STATIC_DRAW);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*6, indices, GL_STATIC_DRAW);
//
//	std::list<Node*>::iterator i;
//	int count = 0;
//	for (i = nodes.begin(); i != nodes.end(); i++)
//	{
//		Node* node = (*i);
//		(*i)->draw();
//		V3F_C3F_T2F vert = node->getVertices()[0];
//		//std::cout << "Render::draw  vert.vertices.x = " << vert.vertices.x << std::endl;
//		//std::cout << "Render::draw  vert.vertices.y = " << vert.vertices.y << std::endl;
//		//std::cout << "Render::draw  node->getIndicesCount() = " << node->getIndicesCount() << std::endl;
//
//		glDrawElements(GL_TRIANGLES, node->getIndicesCount(), GL_UNSIGNED_INT, (GLvoid*)(_triBatchesToDraw[count]*sizeof(_indices[0])));
//		//glDrawElements(GL_TRIANGLES, node->getIndicesCount(), GL_UNSIGNED_INT, (GLvoid*)(0));
//		count += 1;
//	}
//
//
//	glBindVertexArray(0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	
//	_verticesCount = 0;
//	_indicesCount = 0;
//}


void Render::draw()
{

}

