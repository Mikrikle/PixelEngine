#include "PixelEngine.h"
using namespace px;

PxSlider::PxSlider(std::function<void(PxSlider* self)> callback, Orientation orientation, float width, float height, float scale, float posX, float posY, Shader* shader)
	: AbstractRectangle(shader),
	toggle(),
	toggle_route_line()
{
	orientation_ = orientation;
	reInit(width, height);
	setPos(posX, posY);
	setScale(scale);
	callback_ = callback;
	percentages_ = 50.0f;
	stepSize_ = 1;
	mouseGrab_ = false;
	toggle.setColorAsTexture(0.9f, 0.9f, 0.9f);
	toggle_route_line.setColorAsTexture(0.1f, 0.1f, 0.1f);
}

void PxSlider::reInit(float width, float height)
{
	AbstractRectangle::reInit(width, height);
	toggle.reInit((orientation_ == px::Orientation::HORIZONTAL) ? width / 50.0f : width, (orientation_ == px::Orientation::HORIZONTAL) ? height : height / 50.0f);
	toggle_route_line.reInit((orientation_ == px::Orientation::HORIZONTAL) ? width * 0.95f : width / 4.0f, (orientation_ == px::Orientation::HORIZONTAL) ? height / 4.0f : height * 0.95f);
}

void PxSlider::setPercentages()
{
	if (orientation_ == px::Orientation::HORIZONTAL)
	{
		percentages_ = (fabs(toggle.getScaledPos().x - toggle_route_line.getScaledPos().x)) / toggle_route_line.getScaledSIZE().x * 100.0f;
	}
	else
	{
		percentages_ = (fabs(toggle.getScaledPos().y - toggle_route_line.getScaledPos().y)) / toggle_route_line.getScaledSIZE().y * 100.0f;
	}
}

void PxSlider::setStep(int step)
{
	if (step > 0)
	{
		stepSize_ = 100.0f / step;
	}
}

int PxSlider::getValue()
{
	return static_cast<int>(round(percentages_) / stepSize_);
}

void PxSlider::update()
{
	if (isClickOn() || (px::isMouseLeftClick && mouseGrab_))
	{
		px::isMouseAlreadyUsed = true;
		mouseGrab_ = true;
		toggle.setTextureOpacity(activeOpacity_);
		if (callback_ != nullptr)
			callback_(this);
		isPressed_ = true;
		if (orientation_ == px::Orientation::HORIZONTAL)
		{
			if (px::absoluteMousePosX < toggle_route_line.getScaledPos().x + toggle_route_line.getScaledSIZE().x &&
				px::absoluteMousePosX > toggle_route_line.getScaledPos().x)
			{
				toggle.setPos(px::absoluteMousePosX, this->getPos().y);
			}
		}
		else
		{
			if (px::absoluteMousePosY < toggle_route_line.getScaledPos().y + toggle_route_line.getScaledSIZE().y &&
				px::absoluteMousePosY > toggle_route_line.getScaledPos().y)
			{
				toggle.setPos(this->getPos().x, px::absoluteMousePosY);
			}
		}
		setPercentages();
	}
	else
	{
		mouseGrab_ = false;
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

void PxSlider::draw()
{
	AbstractRectangle::draw();
	toggle_route_line.draw();
	toggle.draw();
}

float  PxSlider::getPercentages()
{
	return percentages_;
}

void PxSlider::setScale(float scale)
{
	AbstractRectangle::setScale(scale);
	toggle_route_line.setScale(scale);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.setScale(scale);
}

void PxSlider::IncreaseScale(float value)
{
	AbstractRectangle::IncreaseScale(value);
	toggle_route_line.IncreaseScale(value);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.IncreaseScale(value);
}

void PxSlider::setPos(float x, float y)
{
	AbstractRectangle::setPos(x, y);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.setPos(x, y);
}

void PxSlider::IncreasePos(float moveX, float moveY)
{
	AbstractRectangle::IncreasePos(moveX, moveY);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.IncreasePos(moveX, moveY);
}