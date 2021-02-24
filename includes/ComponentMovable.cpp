#include "PixelEngine.h"
using namespace Px;

ComponentMovable::ComponentMovable(float WIDTH, float HEIGHT) : ComponentBase(WIDTH, HEIGHT)
{
	this->scale = 1.0f;
	this->nullPos = FloatCoord{ -WIDTH / 2.0f, -HEIGHT / 2.0f };
	this->translatePos = FloatCoord{ 0.0f , 0.0f };
	this->absoluteMousePos = FloatCoord{ -1.0f , -1.0f };
	this->realPos = FloatCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };
}

FloatCoord ComponentMovable::getNullPos()
{
	return nullPos;
}

void ComponentMovable::normilizeNullCoords()
{
	nullPos = FloatCoord{ round(nullPos.x * 10000) / 10000, round(nullPos.y * 10000) / 10000 };
}

float ComponentMovable::getScale()
{
	return scale;
}

void ComponentMovable::setScale(float scale)
{
	this->scale = scale;
}

void ComponentMovable::increaseScale(float value)
{
	if ((value > 0 && scale < 50.0) || (value < 0 && scale > 0.1))
		this->scale += value;
}

void ComponentMovable::setTranslate(float x, float y)
{
	nullPos = FloatCoord{ -WIDTH / 2.0f + x, -HEIGHT / 2.0f + y };
	translatePos = FloatCoord{ x, y };
	normilizeNullCoords();
}

void ComponentMovable::increaseTranslate(float moveX, float moveY)
{
	nullPos = FloatCoord{ nullPos.x += moveX, nullPos.y += moveY };
	translatePos.x += moveX;
	translatePos.y += moveY;
	normilizeNullCoords();
}

bool ComponentMovable::isClickOn(int x, int y)
{
	if (x >= 0 && x <= Px::WindowSizeY && y >= 0 && y <= Px::WindowSizeY)
	{
		absoluteMousePos = FloatCoord{ (x / ((float)Px::WindowSizeX / 2.0f)) - 1.0f, (((float)Px::WindowSizeY - y) / ((float)Px::WindowSizeY / 2)) - 1.0f };
		realPos = FloatCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };

		if (absoluteMousePos.x > realPos.x && absoluteMousePos.x < realPos.x + WIDTH * scale &&
			absoluteMousePos.y > realPos.y && absoluteMousePos.y < realPos.y + HEIGHT * scale)
		{
			return true;
		}
	}
	return false;
}