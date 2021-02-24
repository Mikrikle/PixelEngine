#include "PixelEngine.h"
using namespace Px;
float moveSpeed;
int baseMoveMod;


void ComponentEvents::setMoveSpeed(float value)
{
	if (value > 0.0f && value < 100.0f)
		this->moveSpeed = value;
}

void ComponentEvents::setMovable(int value)
{
	if (value >= 0 && value <= FULL)
		baseMoveMod = value;
}

ComponentEvents::ComponentEvents()
{
	this->moveSpeed = 1.0f;
	this->baseMoveMod = FULL;
}
