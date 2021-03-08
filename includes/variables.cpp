#include "PixelEngine.h"

namespace Px
{
	bool MouseLeftClick = false;
	bool MouseRightClick = false;
	float absoluteMousePosX = 0.0f;
	float absoluteMousePosY = 0.0f;
	int MousePosX = 0;
	int MousePosY = 0;
	float ScrollX = 0.0f;
	float ScrollY = 0.0f;
	bool Keys[1024]{ 0 };
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
}