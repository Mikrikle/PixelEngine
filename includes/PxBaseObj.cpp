#include "PixelEngine.h"

bool Px::MouseLeftClick = false;
bool Px::MouseRightClick = false;
int Px::WindowSizeX = 100;
int Px::WindowSizeY = 100;

PxBaseObj::PxBaseObj(float WIDTH, float HEIGHT)
{
	this->WIDTH = WIDTH;
	this->HEIGHT = HEIGHT;
}

float PxBaseObj::getWIDTH()
{
	return WIDTH;
}

float PxBaseObj::getHEIGHT()
{
	return HEIGHT;
}
