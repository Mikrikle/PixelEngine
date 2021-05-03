#include "PixelEngine.h"
using namespace px;

PxCheckBox::PxCheckBox(std::function<void(PxCheckBox* self)> callback, float width, float height, float scale, float posX, float posY, Shader* shader)
	: AbstractRectangle(shader), mark()
{
	reInit(width, height);
	setPos(posX, posY);
	setScale(scale);
	callback_ = callback;
	mark.setColorAsTexture(1.0f, 1.0f, 1.0f);
}

void PxCheckBox::reInit(float width, float height)
{
	AbstractRectangle::reInit(width, height);
	mark.reInit(width * 0.7f, height * 0.7f);
}

void PxCheckBox::draw()
{
	AbstractRectangle::draw();
	if (active_)
	{
		mark.draw();
	}
}

bool PxCheckBox::isActive() const
{
	return active_;
}

void PxCheckBox::update()
{
	if (isClickOn() && !isPressed_)
	{
		px::isMouseAlreadyUsed = true;
		setTextureOpacity(activeOpacity_);
		if (callback_ != nullptr)
			callback_(this);
		isPressed_ = true;
		active_ = !active_;
	}
	else if (isClickOn() && isPressed_)
	{
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

void PxCheckBox::setActive(bool isActive)
{
	active_ = isActive;
}

void PxCheckBox::setScale(float scale)
{
	AbstractRectangle::setScale(scale);
	mark.setScale(scale);
	mark.setPosAtCenterObj(*this);
}

void PxCheckBox::IncreaseScale(float value)
{
	AbstractRectangle::IncreaseScale(value);
	mark.IncreaseScale(value);
	mark.setPosAtCenterObj(*this);
}

void PxCheckBox::setPos(float x, float y)
{
	AbstractRectangle::setPos(x, y);
	mark.setPosAtCenterObj(*this);
}

void PxCheckBox::IncreasePos(float moveX, float moveY)
{
	AbstractRectangle::IncreasePos(moveX, moveY);
	mark.setPosAtCenterObj(*this);
}