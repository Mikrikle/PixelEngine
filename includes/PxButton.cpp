#include "PixelEngine.h"
using namespace Px;


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)())
	: AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(btncallback);
}


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)())
	: AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(btncallback);
}

void PxButton::init(void (*btncallback)())
{
	this->btncallback = btncallback;
}

void PxButton::eventProcessing(float deltaTime)
{
	if (IsLocatedOnObject(Px::MousePosX, Px::MousePosY) && Px::MouseLeftClick)
	{
		btncallback();
		Px::MouseLeftClick = false;
	}
}