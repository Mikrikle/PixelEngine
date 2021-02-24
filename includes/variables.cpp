#include "PixelEngine.h"

namespace Px
{
	bool MouseLeftClick = false;
	bool MouseRightClick = false;
	int WindowSizeX = 100;
	int WindowSizeY = 100;
	int MousePosX = 0;
	int MousePosY = 0;
	float ScrollX = 0.0f;
	float ScrollY = 0.0f;
	bool Keys[1024]{ 0 };
}