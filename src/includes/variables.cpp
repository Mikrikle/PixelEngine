#include "PixelEngine.h"

namespace px
{
	bool isMouseLeftClick = false;
	bool isMouseRightClick = false;
	bool isMouseAlreadyUsed = false;
	float absoluteMousePosX = 0.0f;
	float absoluteMousePosY = 0.0f;
	int mousePosX = 0;
	int mousePosY = 0;
	float mouseScrollX = 0.0f;
	float mouseScrollY = 0.0f;
	bool keyboardKeys[1024]{ 0 };
	float deltaTime = 0.0f;
	float lastFrameTime = 0.0f;

	float transformPixToPctWidth(int pixel_size)
	{
		return static_cast<float>(pixel_size) / px::windowWidth;
	}

	float transformPixToPctHeight(int pixel_size)
	{
		return static_cast<float>(pixel_size) / px::windowHeight;
	}
}