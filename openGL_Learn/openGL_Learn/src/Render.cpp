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
	Node* node = Node::create("res/lamp/Lamp.obj");
	node->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	node->setScale(glm::vec3(0.01f, 0.01f, 0.01f));
	node->setRotation(glm::vec3(90.0f, 0.0f, 0.0f));

	Utils::printMat("node model", node->getModelMat());

	Node* node2 = Node::create("res/floor/Floor.fbx");
	node2->setScale(glm::vec3(0.1f, 0.1f, 0.1f));
	node2->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	node2->setPosition(glm::vec3(-1.0f, -2.0f, -2.0f));

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
	createCameraUBO();
	createDepthFrameBuffer();
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

void Render::createCameraUBO()
{
	glGenBuffers(1, &cameraUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, cameraUBO);
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
	genShadowMapping();


	bool bPostProcessing = false;
	if (bPostProcessing)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	Camera::getInstance()->update();

	glm::mat4 projection = Camera::getInstance()->getProjection();
	glm::mat4 view = Camera::getInstance()->getView();
	glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

	delete outlineShader;
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

	delete outlineShader;
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
		std::cout << "ERROR::FRAMEBUFFER::  is not complete!" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


const unsigned int Render::getSkyBoxTexture()
{
	return cubemapTexture;
}

void Render::createDepthFrameBuffer()
{

	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	glGenFramebuffers(1, &depthFBO);

	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Render::genShadowMapping()
{
	const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	


	Shader shader = Shader("shader/ShadowMappingVS.hlsl", "shader/ShadowMappingFS.hlsl");
	glm::mat4 lightProjection, lightView;
	GLfloat near_plane = 1.0f, far_plane = 7.5f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	//lightProjection = glm::perspective(45.0f, (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, near_plane, far_plane); // Note that if you use a perspective projection matrix you'll have to change the light position as the current light position isn't enough to reflect the whole scene.
	DirectLight* light= (DirectLight*)LightManager::getInstance()->getLight(0);
	glm::vec3 lightDir = light->getDirectioin();
	lightView = glm::lookAt(-lightDir, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;
	// - now render scene from light's point of view
	shader.use();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	for (std::vector<Node*>::iterator iter = nodes.begin(); iter != nodes.end(); iter++)
	{
		(*iter)->genShadowMapping(shader);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 800, 600);

}


void Render::addNode(Node* node)
{
	nodes.push_back(node);
}
