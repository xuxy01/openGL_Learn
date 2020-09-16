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
	transform = glm::translate(transform, postion);
	transform = glm::mat4_cast(rotation) * transform;
	transform = glm::scale(transform, scale);

	return transform;
}

void Node::setScale(glm::vec3 newScale)
{
	scale = newScale;
}


void Node::setPosition(glm::vec3 newPosition)
{
	postion = newPosition;
}
void Node::setRotation(glm::vec3 EulerAngles)
{
	rotation = glm::quat(glm::radians(EulerAngles));
}

void Node::draw()
{
	glm::mat4 transform = getModelMat();

	if (model)
	{
		shaderProgram->use();
		shaderProgram->setMat4("projection", glm::value_ptr(Camera::getInstance()->getProjection()));
		shaderProgram->setMat4("view", glm::value_ptr(Camera::getInstance()->getView()));
		shaderProgram->setMat4("model", glm::value_ptr(transform));
		model->Draw(*shaderProgram, transform);
	}

	for (std::vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->draw();
	}
}
