#include "PixelEngine.h"
using namespace px;

PxSwitch::PxSwitch(std::function<void(PxSwitch* self)> callback, Orientation orientation, float width, float height, float scale, float posX, float posY, Shader* shader)
	: AbstractRectangle(shader),
	toggle()
{
	orientation_ = orientation;
	reInit(width, height);
	setPos(posX, posY);
	setScale(scale);
	callback_ = callback;
	toggle.setColorAsTexture(1.0f, 1.0f, 1.0f);
}

void PxSwitch::reInit(float width, float height)
{
	AbstractRectangle::reInit(width, height);
	toggle.reInit((orientation_ == px::Orientation::HORIZONTAL) ? width / 2 : width, (orientation_ == px::Orientation::HORIZONTAL) ? height : height / 2);
}

void PxSwitch::draw()
{
	AbstractRectangle::draw();
	toggle.draw();
}

bool PxSwitch::isActive() const
{
	return active_;
}

void PxSwitch::update()
{
	if (isClickOn() && !isPressed_)
	{
		px::isMouseAlreadyUsed = true;
		toggle.setTextureOpacity(activeOpacity_);
		if (callback_ != nullptr)
			callback_(this);
		isPressed_ = true;
		active_ = !active_;
		setTogglePos();
	}
	else if (isClickOn() && isPressed_)
	{
		px::isMouseAlreadyUsed = true;
	}
	else
	{
		if (isMouseOn())
		{
			toggle.setTextureOpacity(mouseOnOpacity_);
		}
		else
		{
			toggle.setTextureOpacity(normalOpacity_);
		}
		isPressed_ = false;
	}
}

void PxSwitch::setScale(float scale)
{
	AbstractRectangle::setScale(scale);
	toggle.setScale(scale);
	setTogglePos();
}

void PxSwitch::IncreaseScale(float value)
{
	AbstractRectangle::IncreaseScale(value);
	toggle.IncreaseScale(value);
	setTogglePos();
}

void PxSwitch::setPos(float x, float y)
{
	AbstractRectangle::setPos(x, y);
	setTogglePos();
}

void PxSwitch::IncreasePos(float moveX, float moveY)
{
	AbstractRectangle::IncreasePos(moveX, moveY);
	setTogglePos();
}

void PxSwitch::setActive(bool isActive)
{
	active_ = isActive;
	setTogglePos();
}

void PxSwitch::setTogglePos()
{
	if (active_)
	{
		if (orientation_ == px::Orientation::HORIZONTAL)
		{
			toggle.setPos(this->getPos().x + this->getScaledSIZE().x / 2, this->getPos().y);
		}
		else
		{
			toggle.setPos(this->getPos().x, this->getPos().y + this->getScaledSIZE().y / 2);
		}
	}
	else
	{
		if (orientation_ == px::Orientation::HORIZONTAL)
		{
			toggle.setPos(this->getPos().x, this->getPos().y);
		}
		else
		{
			toggle.setPos(this->getPos().x, this->getPos().y);
		}
	}
}