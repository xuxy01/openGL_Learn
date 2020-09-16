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