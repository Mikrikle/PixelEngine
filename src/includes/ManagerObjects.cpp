#include "PixelEngine.h"
using namespace px;

ManagerObjects::ManagerObjects()
{
}

void ManagerObjects::init(std::initializer_list<engine::ComponentBase*> objects)
{
	objects_ = objects;
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
	for (int i = 0; i < objects_.size(); ++i)
	{
		if (!isInDrawIgnore(i))
		{
			objects_[i]->draw();
		}
	}
}

void ManagerObjects::updateAll()
{
	for (int i = 0; i < objects_.size(); ++i)
	{
		if (!isInUpdateIgnore(i))
		{
			objects_[i]->update();
		}
	}
}

void ManagerObjects::addToIgnoreDrawingLsist(int index)
{
	ignoreDrawList_.insert(index);
}

void ManagerObjects::addToIgnoreUpdatingLsist(int index)
{
	ignoreUpdateList_.insert(index);
}

void ManagerObjects::removeFromIgnoreDrawingList(int index)
{
	ignoreDrawList_.erase(index);
}

void ManagerObjects::removeFromIgnoreUpdatingList(int index)
{
	ignoreUpdateList_.erase(index);
}

bool ManagerObjects::isInDrawIgnore(int index)
{
	return (std::find(ignoreDrawList_.begin(), ignoreDrawList_.end(), index) == ignoreDrawList_.end()) ? false : true;
}

bool ManagerObjects::isInUpdateIgnore(int index)
{
	return (std::find(ignoreUpdateList_.begin(), ignoreUpdateList_.end(), index) == ignoreUpdateList_.end()) ? false : true;
}