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
	init();
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


void Render::init()
{
	createFrameBuffer();
	createScreenVAO();
	createSkyBoxVAO();
}

void Render::createScreenVAO()
{

	float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}


void Render::createSkyBoxVAO()
{
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	glGenVertexArrays(1, &skyBoxVAO);
	glGenBuffers(1, &skyBoxVBO);
	glBindVertexArray(skyBoxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


	std::vector<std::string> faces
	{
		"./res/Skyboxes/_Skybox/Sky_02.jpg",
		"./res/Skyboxes/_Skybox/Sky_04.jpg",
		"./res/Skyboxes/_Skybox/Sky_05.jpg",
		"./res/Skyboxes/_Skybox/Sky_06.jpg",
		"./res/Skyboxes/_Skybox/Sky_01.jpg",
		"./res/Skyboxes/_Skybox/Sky_03.jpg",
	};
	cubemapTexture = Utils::loadCubemap(faces);
	//cubemapTexture = Utils::TextureFromFile(faces[4].c_str(), "./", false);

	std::cout << "cubemapTexture = " << cubemapTexture << std::endl;
}

void Render::draw()
{
	bool bPostProcessing = false;
	if (bPostProcessing)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	Camera::getInstance()->update();
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		(*iter)->draw();
	}

	renderSkyBox();

	if (bPostProcessing)
	{
		renderScreen();
	}


}

void Render::renderSkyBox()
{

	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	Shader* outlineShader = new Shader("shader/SkyBoxVertexShader.hlsl", "shader/SkyBoxFragmentShader.hlsl");
	outlineShader->use();
	glm::mat4 view =glm::mat4(glm::mat3( Camera::getInstance()->getView()));
	//glm::mat4 view = glm::mat4(Camera::getInstance()->getView());
	glm::mat4 projection = Camera::getInstance()->getProjection();
	outlineShader->setMat4("view",glm::value_ptr(view));
	outlineShader->setMat4("projection", glm::value_ptr(projection));

	outlineShader->setInt("skybox", 0);
	glBindVertexArray(skyBoxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	//glBindTexture(GL_TEXTURE_2D, cubemapTexture);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void Render::renderScreen()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(quadVAO);

	Shader* outlineShader = new Shader("shader/ScreenVertexShader.hlsl", "shader/ScreenFragmentShader.hlsl");
	outlineShader->use();

	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Render::createFrameBuffer()
{
	glGenFramebuffers(1, &fbo);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);


	glGenTextures(1, &textureColorbuffer);

	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);

	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);

	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::addNode(Node* node)
{
	nodes.push_back(node);
}
