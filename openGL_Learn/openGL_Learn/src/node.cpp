#include "node.h"


Node* Node::create() {
	Node* node = new Node();
	node->init();

	return node;
}

Node* Node::create(std::string path)
{
	Node* node = new Node();
	node->init();

	if (path.empty())
		return node;

	ModelObject* model = new ModelObject(path.c_str());
	node->setModel(model);

	return node;
}


Node::Node() :
	postion(glm::vec3(0.0f, 0.0f, 0.0f)),
	scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	rotation(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f))),

	model(nullptr)
{

}

Node::~Node()
{
}

void Node::init()
{
	shaderProgram = new Shader("shader/CommonVertexShader.hlsl", "shader/CommonFragmentShader.hlsl");
}

void Node::setModel(ModelObject* newModel)
{
	model = newModel;
}
void Node::addChild(Node* child)
{
	children.push_back(child);
}

void Node::removeChild(Node* child)
{
	for (std::vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++)
	{
		if (*iter == child)
		{
			children.erase(iter);
			break;
		}
	}

}


glm::mat4 Node::getModelMat()
{
	glm::mat4 transform = glm::mat4(1.0f);
	transform = glm::translate(transform, glm::vec3(0.0f,0.0f,0.0f));
	transform = glm::mat4_cast(rotation) * transform;
	transform = glm::scale(transform, scale);

	return transform;
}

void Node::draw()
{
	glm::mat4 transform = getModelMat();

	if (model)
	{
		model->Draw(*shaderProgram, transform);
	}

	for (std::vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->draw();
	}
}
