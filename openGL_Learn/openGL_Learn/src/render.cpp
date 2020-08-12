#include "render.h"

#include <iostream>

static Render* _instance = nullptr;

Render::Render()
{
}

Render::~Render()
{
}

void Render::draw()
{

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

Render* Render::getInstance()
{
	if (!_instance )
	{
		_instance = new (std::nothrow) Render();

	}

	return _instance;
}