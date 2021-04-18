#include "PixelEngine.h"
using namespace px;

void ManagerPercentagesPosition::placeHorizontally(std::vector<engine::ComponentBase*> objects, float offset)
{
	for (auto it = objects.begin() + 1, end = objects.end(); it != end; ++it)
	{
		(*it)->setPosRelativeTo(*(*(it - 1)), RelativeBindingType::SIDE_RIGHT, offset, 0.0f);
	}
}

void ManagerPercentagesPosition::placeVertically(std::vector<engine::ComponentBase*> objects, float offset)
{
	for (auto it = objects.begin() + 1, end = objects.end(); it != end; ++it)
	{
		(*it)->setPosRelativeTo(*(*(it - 1)), RelativeBindingType::SIDE_BOTTOM, 0.0f, -offset);
	}
}