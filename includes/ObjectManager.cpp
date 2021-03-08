#include "PixelEngine.h"
using namespace Px;

void ObjectManager::drawAll()
{
	for (int i = 0; i < objectsCounter; i++)
	{
		objects[i]->draw();
	}
}

void Px::ObjectManager::updateAll()
{
	for (int i = 0; i < objectsCounter; i++)
	{
		objects[i]->update();
	}
}

ObjectManager::ObjectManager()
{
	this->objectsCounter = 0;
	this->objects = nullptr;
}

ObjectManager::~ObjectManager()
{
	delete[] objects;
}

void ObjectManager::appendObj(ComponentBase& obj)
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

void ObjectManager::appendObjects(int n, ComponentBase* objects[])
{
	for (int i = 0; i < n; i++)
	{
		appendObj((*objects[i]));
	}
}