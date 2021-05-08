#include "PixelEngine.h"
using namespace px;

PxSlider::PxSlider(std::function<void(PxSlider* self)> callback, Orientation orientation, float width, float height, float scale, float posX, float posY, Shader* shader)
	: AbstractRectangle(shader),
	toggle(),
	toggle_route_line()
{
	orientation_ = orientation;
	if (orientation_ == px::Orientation::HORIZONTAL)
	{
		toggleWidthRatio_ = 0.02f;
		toggleHeightRatio_ = 1.0f;
		toggleRouteLineWidthRatio_ = 0.85f;
		toggleRouteLineHeightRatio_ = 0.25f;
	}
	else
	{
		toggleWidthRatio_ = 1.0f;
		toggleHeightRatio_ = 0.02f;
		toggleRouteLineWidthRatio_ = 0.25f;
		toggleRouteLineHeightRatio_ = 0.85f;
	}
	reInit(width, height);
	setPos(posX, posY);
	setScale(scale);
	callback_ = callback;
	toggle.setColorAsTexture(0.9f, 0.9f, 0.9f);
	toggle_route_line.setColorAsTexture(0.1f, 0.1f, 0.1f);
}

void PxSlider::reInit(float width, float height)
{
	AbstractRectangle::reInit(width, height);
	toggle.reInit( width * toggleWidthRatio_, height * toggleHeightRatio_);
	toggle_route_line.reInit(width * toggleRouteLineWidthRatio_, height * toggleRouteLineHeightRatio_ );
}


void PxSlider::setToggleWidth(float width)
{
	if (width <= 1 && width > 0)
	{
		toggleWidthRatio_ = width;
		toggle.reInit(width * toggleRouteLineWidthRatio_, toggle.getSIZE().y);
	}
}
void PxSlider::setToggleHeight(float height)
{
	if (height <= 1 && height > 0)
	{
		toggleHeightRatio_ = height;
		toggle.reInit(toggle.getSIZE().x, height * toggleHeightRatio_);
	}
}
void PxSlider::setToggleRouteLineWidth(float width)
{
	if (width <= 1 && width > 0)
	{
		toggleRouteLineWidthRatio_ = width;
		toggle_route_line.reInit(width * toggleRouteLineWidthRatio_, toggle_route_line.getSIZE().y);
		toggle_route_line.setPosAtCenterObj(*this);
	}
}
void PxSlider::setToggleRouteLineHeight(float height)
{
	if (height <= 1 && height > 0)
	{
		toggleRouteLineHeightRatio_ = height;
		toggle_route_line.reInit(toggle_route_line.getSIZE().x, height * toggleRouteLineHeightRatio_);
		toggle_route_line.setPosAtCenterObj(*this);
	}
}

void PxSlider::setPercentages()
{
	if (orientation_ == px::Orientation::HORIZONTAL)
	{
		percentages_ = (fabs(toggle.getCenterPos().x - toggle_route_line.getPos().x)) / toggle_route_line.getScaledSIZE().x * 100.0f;
	}
	else
	{
		percentages_ = (fabs(toggle.getCenterPos().y - toggle_route_line.getPos().y)) / toggle_route_line.getScaledSIZE().y * 100.0f;
	}
}

void PxSlider::setStep(int step)
{
	if (step > 0)
	{
		stepSize_ = 100.0f / step;
	}
}

int PxSlider::getValue() const
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
			if (px::absoluteMousePosX <= toggle_route_line.getPos().x + toggle_route_line.getScaledSIZE().x &&
				px::absoluteMousePosX >= toggle_route_line.getPos().x)
			{
				toggle.setPos(px::absoluteMousePosX - toggle.getSIZE().x/2.0f, this->getPos().y);
			}
			else if (px::absoluteMousePosX <= toggle_route_line.getPos().x + toggle_route_line.getScaledSIZE().x)
			{
				toggle.setPos(toggle_route_line.getPos().x - toggle.getSIZE().x / 2.0f, this->getPos().y);
			}
			else if (px::absoluteMousePosX >= toggle_route_line.getPos().x)
			{
				toggle.setPos(toggle_route_line.getPos().x + toggle_route_line.getScaledSIZE().x - toggle.getSIZE().x / 2.0f, this->getPos().y);
			}
		}
		else
		{
			if (px::absoluteMousePosY <= toggle_route_line.getPos().y + toggle_route_line.getScaledSIZE().y &&
				px::absoluteMousePosY >= toggle_route_line.getPos().y)
			{
				toggle.setPos(this->getPos().x, px::absoluteMousePosY - toggle.getSIZE().y / 2.0f);
			}
			else if (px::absoluteMousePosY <= toggle_route_line.getPos().y + toggle_route_line.getScaledSIZE().y)
			{
				toggle.setPos(this->getPos().x, toggle_route_line.getPos().y - toggle.getSIZE().y / 2.0f);
			}
			else if (px::absoluteMousePosY >= toggle_route_line.getPos().y)
			{
				toggle.setPos(this->getPos().x, toggle_route_line.getPos().y + toggle_route_line.getScaledSIZE().y - toggle.getSIZE().y / 2.0f);
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

float  PxSlider::getPercentages() const
{
	return percentages_;
}

void PxSlider::setScale(float scale)
{
	AbstractRectangle::setScale(scale);
	toggle_route_line.setScale(scale);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.setScale(scale);
	toggle.setPosAtCenterObj(toggle_route_line);
}

void PxSlider::IncreaseScale(float value)
{
	AbstractRectangle::IncreaseScale(value);
	toggle_route_line.IncreaseScale(value);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.IncreaseScale(value);
	toggle.setPosAtCenterObj(toggle_route_line);
}

void PxSlider::setPos(float x, float y)
{
	AbstractRectangle::setPos(x, y);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.setPosAtCenterObj(toggle_route_line);
}

void PxSlider::IncreasePos(float moveX, float moveY)
{
	AbstractRectangle::IncreasePos(moveX, moveY);
	toggle_route_line.setPosAtCenterObj(*this);
	toggle.setPosAtCenterObj(toggle_route_line);
}