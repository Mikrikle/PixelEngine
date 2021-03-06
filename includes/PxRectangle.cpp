#include "../includes/PixelEngine.h"
using namespace Px;

PxRectangle::PxRectangle(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY,
	void (*event_click)(PxRectangle& self), void (*event_scrool)(PxRectangle& self), void (*event_keyboard)(PxRectangle& self, float deltaTime)) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(event_click, event_scrool, event_keyboard);
}

PxRectangle::PxRectangle(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY,
	void (*event_click)(PxRectangle& self), void (*event_scrool)(PxRectangle& self), void (*event_keyboard)(PxRectangle& self, float deltaTime)) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(event_click, event_scrool, event_keyboard);
}

void PxRectangle::init(void (*event_click)(PxRectangle& self), void (*event_scrool)(PxRectangle& self), void (*event_keyboard)(PxRectangle& self, float deltaTime))
{
	this->event_click = event_click;
	this->event_scrool = event_scrool;
	this->event_keyboard = event_keyboard;
	genTexture();
}


void PxRectangle::eventProcessing(float deltaTime)
{

	if (event_scrool != nullptr && (Px::ScrollX != 0 || Px::ScrollY != 0))
	{
		event_scrool(*(this));
	}

	if (event_keyboard != nullptr)
	{
		event_keyboard(*(this), deltaTime);
	}

	if (event_click != nullptr && (Px::MouseLeftClick || Px::MouseRightClick) && IsLocatedOnObject(Px::MousePosX, Px::MousePosY))
	{

		event_click(*(this));
	}

}