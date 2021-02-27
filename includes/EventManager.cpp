#include "PixelEngine.h"
using namespace Px;

void EventsDefaultManager::updateEvents(float deltaTime)
{
	for (int i = 0; i < objectsCounter; i++)
	{
		objects[i]->eventProcessing(deltaTime);
	}
}

EventsDefaultManager::EventsDefaultManager()
{
	this->objectsCounter = 0;
	this->objects = nullptr;
}

EventsDefaultManager::~EventsDefaultManager()
{
	delete[] objects;	
}

void EventsDefaultManager::appendObj(ComponentEvents& obj)
{
	this->objectsCounter++;
	ComponentEvents** newobjects = new ComponentEvents *[this->objectsCounter];
	for (int i = 0; i < objectsCounter-1; i++)
	{
		newobjects[i] = objects[i];
	}
	newobjects[objectsCounter - 1] = &obj;
	delete[] this->objects;
	this->objects = newobjects;
}

void EventsDefaultManager::appendObjects(int n, ComponentEvents* objects[])
{
	for (int i = 0; i < n; i++)
	{
		appendObj((*objects[i]));
	}
}