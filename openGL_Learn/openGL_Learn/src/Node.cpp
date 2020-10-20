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
	transform = transform * glm::mat4_cast(rotation);
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

	if (model)
	{
		shaderProgram->use();
		glm::mat4 transform = getModelMat();
		//shaderProgram->setMat4("projection", glm::value_ptr(Camera::getInstance()->getProjection()));
		//shaderProgram->setMat4("view", glm::value_ptr(Camera::getInstance()->getView()));
		shaderProgram->setMat4("model", glm::value_ptr(transform));

		shaderProgram->setMat4("lightSpaceMatrix", glm::value_ptr(Render::getInstance()->getLightSpaceMatrix()));

		unsigned int uniformblockIndexCamera = glGetUniformBlockIndex(shaderProgram->ID, "Matrices");
		glUniformBlockBinding(shaderProgram->ID, uniformblockIndexCamera, 0);

		LightManager::getInstance()->use(shaderProgram);
		
		shaderProgram->setFloat3("viewPos", Camera::getInstance()->getPosition());

		shaderProgram->setInt("skybox", 10);
		
		glActiveTexture(GL_TEXTURE0+10);
		glBindTexture(GL_TEXTURE_CUBE_MAP, Render::getInstance()->getSkyBoxTexture());

		bool bDrawOutline = false;
		if (bDrawOutline)
		{
			glEnable(GL_STENCIL_TEST);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 1, 0xFF);

			model->Draw(*shaderProgram, transform);

			glStencilMask(0x00);
			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glDisable(GL_DEPTH_TEST);

			Shader* outlineShader = new Shader("shader/OutlineVertexShader.hlsl", "shader/OutlineFragmentShader.hlsl");
			outlineShader->use();
			glm::mat4 transform = getModelMat();
			outlineShader->setMat4("projection", glm::value_ptr(Camera::getInstance()->getProjection()));
			outlineShader->setMat4("view", glm::value_ptr(Camera::getInstance()->getView()));
			outlineShader->setMat4("model", glm::value_ptr(transform));
			model->Draw(*outlineShader, transform);
			glStencilMask(0xFF);
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_STENCIL_TEST);
			delete outlineShader;
		}
		else
		{
			model->Draw(*shaderProgram, transform);
		}
	}

	for (std::vector<Node*>::iterator iter = children.begin(); iter != children.end(); iter++)
	{
		(*iter)->draw();
	}
}

void Node::genShadowMapping(Shader shader)
{

}
