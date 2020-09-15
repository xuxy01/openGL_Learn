#include "node.h"

Node::Node() :
	_verticesCount(0),
	_indicesCount(0),

	postion(glm::vec3(0.0f,0.0f,0.0f)),
	scale(glm::vec3(1.0f, 1.0f, 1.0f)),
	rotation(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)))
{

}

Node::~Node()
{
	clean();
}

Node* Node::create() {
	Node* node = new Node();
	node->init();

	node->_vertices[0] = V3F_C3F_T2F(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
	node->_vertices[1] = V3F_C3F_T2F(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f));
	node->_vertices[2] = V3F_C3F_T2F(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f));
	node->_vertices[3] = V3F_C3F_T2F(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f));

	return node;
}

Node* Node::create(V3F_C3F_T2F* vertices,unsigned int lenght) {
	Node* node = new Node();
	node->init();

	for (int i = 0; i < lenght; i++)
		node->_vertices[i] = vertices[i];

	return node;
}


void Node::init()
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left 
	};

	

	unsigned int indices[] = {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 3;
	_indices[3] = 1;
	_indices[4] = 2;
	_indices[5] = 3;


	_verticesCount = 4;
	_indicesCount = 6;


	shaderProgram = new Shader("shader/CommonVertexShader.hlsl", "shader/CommonFragmentShader.hlsl");


	//setTexture("res/vip_black_quarterly.png");
}

void Node::draw()
{

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	shaderProgram->use();
	shaderProgram->setFloat4("baseColor", 1.0f, 1.0f, 0.0f, 1.0f);
	float timeValue = glfwGetTime();
	shaderProgram->setFloat("time", timeValue);
	shaderProgram->setInt("texture0", 0);

	glm::mat4 view = Camera::getInstance()->getView();
	glm::mat4 projection = Camera::getInstance()->getProjection();

	shaderProgram->setMat4("view", glm::value_ptr<float>(projection*view));


	//shaderProgram->setMat4("projection", glm::value_ptr<float>(projection));


	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, postion);
	model = glm::mat4_cast(rotation) * model;
	model = glm::scale(model, scale);

	shaderProgram->setMat4("model", glm::value_ptr<float>(model));

	//glm::vec4 pos = { 0.5f,  0.5f, 0.0f, 1.0f };

	//pos =  (projection * view * model) * pos;

	//std::cout << "new pos =" << pos.x << "," << pos.y << "," << pos.z << "," << pos.w << std::endl;

	/*glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE, texture);
	shaderProgram->setInt("texture1", 1);*/


}


void Node::setTexture(const char* imagePath)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(imagePath, &width, &height, &nrChannels, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}


	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

}


void Node::clean()
{
}
