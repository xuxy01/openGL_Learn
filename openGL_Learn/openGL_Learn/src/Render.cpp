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
	Node* node = Node::create("res/humen/rp_sophia_animated_003_idling.fbx");
	node->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	node->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));


	Node* node2 = Node::create("res/humen/rp_sophia_animated_003_idling.fbx");
	node2->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	node2->setPosition(glm::vec3(-1.0f, 0.0f, -2.0f));

	addNode(node);
	addNode(node2);

	DirectLight* light = new DirectLight();
	LightManager::getInstance()->addLight(light);

}

Render::~Render()
{
}


#define offsetof(s,m) ((::size_t)&reinterpret_cast<char const volatile&>((((s*)0)->m)))

void Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera::getInstance()->update();
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		(*iter)->draw();
	}
}

void Render::addNode(Node* node)
{
	nodes.push_back(node);
}
