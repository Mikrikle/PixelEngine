#include "PixelEngine.h"
using namespace px;
using namespace engine;

ComponentBase::ComponentBase(float width, float height)
{
	size_ = FloatCoord{ width, height };
	nullPos_ = FloatCoord{ -width / 2.0f, -height / 2.0f };
	transformMatrix_ = glm::mat4(1.0f);
	normilizeNullCoords();
}

FloatCoord ComponentBase::getCenterPos() const
{
	return FloatCoord{ getPos().x + getScaledSIZE().x / 2, getPos().y + getScaledSIZE().y / 2 };
}

FloatCoord ComponentBase::getSIZE() const
{
	return size_;
}

FloatCoord ComponentBase::getPos() const
{
	return nullPos_;
}

void ComponentBase::normilizeNullCoords()
{
	nullPos_ = FloatCoord{ round(nullPos_.x * 10000) / 10000, round(nullPos_.y * 10000) / 10000 };
}

float ComponentBase::getScale() const
{
	return scale_;
}

void ComponentBase::setScale(float scale)
{
	if (scale < 1000.0 && scale > 0.01)
		scale_ = scale;
	else
		PxError::show(PxError::Error::INVALID_VALUE, "setScale", "scale must be more than 0.01 and less than 1000");
}

FloatCoord ComponentBase::getScaledSIZE() const
{
	return FloatCoord{ size_.x * scale_, size_.y * scale_ };
}

void ComponentBase::IncreaseScale(float value)
{
	if ((value > 0 && scale_ + value < 1000.0) || (value < 0 && scale_ + value > 0.01))
		scale_ += value;
	else
		PxError::show(PxError::Error::INVALID_VALUE, "IncreaseScale", "scale must be more than 0.01 and less than 1000");
}

void ComponentBase::setPos(float x, float y)
{
	nullPos_ = FloatCoord{ x, y };
	normilizeNullCoords();
}

void ComponentBase::setPosAtCenter()
{
	setPos(-getScaledSIZE().x / 2, -getScaledSIZE().y / 2);
}

void ComponentBase::setPosAtCenterObj(ComponentBase& obj)
{
	setPos(obj.getPos().x + (obj.getScaledSIZE().x - this->getScaledSIZE().x) / 2.0f, obj.getPos().y + (obj.getScaledSIZE().y - this->getScaledSIZE().y) / 2.0f);
}

void ComponentBase::setPosRelativeTo(ComponentBase& obj, RelativeBindingType side, float offsetX, float offsetY)
{
	switch (side)
	{
	case RelativeBindingType::SIDE_LEFT:

		setPos(obj.getPos().x - this->getScaledSIZE().x + offsetX, obj.getPos().y + offsetY);
		break;

	case RelativeBindingType::SIDE_RIGHT:

		setPos(obj.getPos().x + obj.getScaledSIZE().x + offsetX, obj.getPos().y + offsetY);
		break;

	case RelativeBindingType::SIDE_TOP:

		setPos(obj.getPos().x + offsetX, obj.getPos().y + obj.getScaledSIZE().y + offsetY);
		break;

	case RelativeBindingType::SIDE_BOTTOM:

		setPos(obj.getPos().x + offsetX, obj.getPos().y - this->getScaledSIZE().y + offsetY);
		break;
	}
}

void ComponentBase::setPosAtAbsoluteGrid(int row_num, int col_num)
{
	float rowSize = 2.0f * getScaledSIZE().x;
	float colSize = 2.0f * getScaledSIZE().y;
	setPos(-1.0f + colSize * col_num + getScaledSIZE().x / 2, -1.0f + rowSize * row_num + getScaledSIZE().y / 2);
}

void ComponentBase::IncreasePos(float moveX, float moveY)
{
	nullPos_ = FloatCoord{ nullPos_.x += moveX, nullPos_.y += moveY };
	normilizeNullCoords();
}

bool ComponentBase::isMouseOn() const
{
	if (px::mousePosX >= 0 && px::mousePosX <= px::windowWidth && px::mousePosY >= 0 && px::mousePosY <= px::windowHeight)
	{
		if (px::absoluteMousePosX > nullPos_.x && px::absoluteMousePosX  < nullPos_.x + getScaledSIZE().x &&
			px::absoluteMousePosY > nullPos_.y && px::absoluteMousePosY < nullPos_.y + getScaledSIZE().y)
		{
			return true;
		}
	}
	return false;
}

bool ComponentBase::isClickOn() const
{
	if (isMouseOn() && px::isMouseLeftClick && !px::isMouseAlreadyUsed)
		return true;
	return false;
}