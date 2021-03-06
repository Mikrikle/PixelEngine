#include "PixelEngine.h"
using namespace Px;

ComponentBase::ComponentBase(float WIDTH, float HEIGHT)
{
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

ComponentBase::ComponentBase()
{
	this->WIDTH = 1;
	this->HEIGHT = 1;
}

float ComponentBase::getWIDTH()
{
	return WIDTH;
}

float ComponentBase::getHEIGHT()
{
	return HEIGHT;
}

FloatCoord ComponentBase::getSIZE()
{
	return FloatCoord{ WIDTH, HEIGHT };
}