#include "LightManagere.h"


static LightManager* _instance = nullptr;

LightManager* LightManager::getInstance()
{
	if (!_instance)
	{
		_instance = new (std::nothrow) LightManager();

	}

	return _instance;
}


LightManager::LightManager()
{

}
LightManager::~LightManager()
{

}

void LightManager::addLight(Light* light)
{
	lights.push_back(light);
}

void LightManager::use(Shader* shader)
{
	for (std::vector<Light*>::iterator iter = lights.begin(); iter != lights.end(); iter++)
	{
		(*iter)->use(shader);
	}
}
