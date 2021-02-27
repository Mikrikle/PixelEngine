#include "PixelEngine.h"
using namespace Px;

void DrawManager::drawAll()
{
	for (int i = 0; i < objectsCounter; i++)
	{
		objects[i]->draw();
	}
}

DrawManager::DrawManager()
{
	this->objectsCounter = 0;
	this->objects = nullptr;
}

DrawManager::~DrawManager()
{
	delete[] objects;
}

void DrawManager::appendObj(ComponentBase& obj)
{
	this->objectsCounter++;
	ComponentBase** newobjects = new ComponentBase * [this->objectsCounter];
	for (int i = 0; i < objectsCounter - 1; i++)
	{
		newobjects[i] = objects[i];
	}
	newobjects[objectsCounter - 1] = &obj;
	delete[] this->objects;
	this->objects = newobjects;
}

void DrawManager::appendObjects(int n, ComponentBase* objects[])
{
	for (int i = 0; i < n; i++)
	{
		appendObj((*objects[i]));
	}
}