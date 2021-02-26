#include "PixelEngine.h"
using namespace Px;
float moveSpeed;
int baseMoveMod;


void ComponentEvents::setMoveSpeed(float value)
{
	if (value > 0.0f && value < 100.0f)
		this->moveSpeed = value;
}

float ComponentEvents::getMoveSpeed()
{
	return moveSpeed;
}

ComponentEvents::ComponentEvents()
{
	this->moveSpeed = 1.0f;
}
