#include "PixelEngine.h"

PxMovableObj::PxMovableObj(float WIDTH, float HEIGHT) : PxBaseObj(WIDTH, HEIGHT)
{
	this->scale = 1.0f;
	this->nullPos = PxCoord{ -WIDTH / 2.0f, -HEIGHT / 2.0f };
	this->translatePos = PxCoord{ 0.0f , 0.0f };
	this->absoluteMousePos = PxCoord{ -1.0f , -1.0f };
	this->realPos = PxCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };
}

PxCoord PxMovableObj::getNullPos()
{
	return nullPos;
}

void PxMovableObj::normilizeNullCoords()
{
	nullPos = PxCoord{ round(nullPos.x * 100) / 100, round(nullPos.y * 100) / 100 };
}

float PxMovableObj::getScale()
{
	return scale;
}

void PxMovableObj::setScale(float scale)
{
	this->scale = scale;
}

void PxMovableObj::increaseScale(float value)
{
	if ((value > 0 && scale < 50.0) || (value < 0 && scale > 0.1))
		this->scale += value;
}

void PxMovableObj::setTranslate(float x, float y)
{
	nullPos = PxCoord{ -WIDTH / 2.0f + x, -HEIGHT / 2.0f + y };
	translatePos = PxCoord{ x, y };
	normilizeNullCoords();
}

void PxMovableObj::increaseTranslate(float moveX, float moveY)
{
	nullPos = PxCoord{ nullPos.x += moveX, nullPos.y += moveY };
	translatePos.x += moveX;
	translatePos.y += moveY;
	normilizeNullCoords();
}

bool PxMovableObj::isClickOn(int x, int y)
{
	absoluteMousePos = PxCoord{ (x / ((float)Px::WindowSizeX / 2.0f)) - 1.0f, (((float)Px::WindowSizeY - y) / ((float)Px::WindowSizeY / 2)) - 1.0f };
	realPos = PxCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };

	if (absoluteMousePos.x > realPos.x && absoluteMousePos.x < realPos.x + WIDTH * scale &&
		absoluteMousePos.y > realPos.y && absoluteMousePos.y < realPos.y + HEIGHT * scale)
	{
		return true;
	}
	return false;
}