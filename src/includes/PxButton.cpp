#include "PixelEngine.h"
using namespace px;

PxButton::PxButton(std::function<void(PxButton* self)> callback, float width, float height, float scale, float posX, float posY, Shader* shader)
	: AbstractRectangle(width, height, shader)
{
	setPos(posX, posY);
	setScale(scale);
	callback_ = callback;
}

void PxButton::update()
{
	if (isClickOn() && !isPressed_)
	{
		px::isMouseAlreadyUsed = true;
		setTextureOpacity(activeOpacity_);
		if (callback_ != nullptr)
			callback_(this);
		isPressed_ = true;
	}
	else if (isMouseOn() && px::isMouseLeftClick)
	{
		setTextureOpacity(activeOpacity_);
		px::isMouseAlreadyUsed = true;
	}
	else
	{
		if (isMouseOn())
		{
			setTextureOpacity(mouseOnOpacity_);
		}
		else
		{
			setTextureOpacity(normalOpacity_);
		}
		isPressed_ = false;
	}
}