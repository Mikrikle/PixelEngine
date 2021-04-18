#include "PixelEngine.h"
using namespace px;

ManagerObjects::ManagerObjects()
{
}

ManagerObjects::ManagerObjects(std::vector<engine::ComponentBase*> objects)
{
	objects_ = objects;
}

ManagerObjects::ManagerObjects(std::initializer_list<engine::ComponentBase*> objects)
{
	objects_ = objects;
}

void ManagerObjects::appendObj(engine::ComponentBase* obj)
{
	objects_.push_back(obj);
}

void ManagerObjects::drawAll()
{
	for (auto it = objects_.begin(), end = objects_.end(); it != end; ++it)
	{
		(*it)->draw();
	}
}

void px::ManagerObjects::updateAll()
{
	for (auto it = objects_.rbegin(), end = objects_.rend(); it != end; ++it)
	{
		(*it)->update();
	}
}