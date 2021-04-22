#include "PixelEngine.h"
using namespace px;
using namespace engine;

ComponentBase::ComponentBase(float width, float height)
{
	size_ = FloatCoord{ width, height };
	scale_ = 1.0f;
	nullPos_ = FloatCoord{ -width / 2.0f, -height / 2.0f };
	transformMatrix_ = glm::mat4(1.0f);
	normilizeNullCoords();
}

FloatCoord ComponentBase::getCenterPos()
{
	return FloatCoord{ getScaledPos().x + getScaledSIZE().x / 2, getScaledPos().y + getScaledSIZE().y / 2 };
}

FloatCoord ComponentBase::getSIZE()
{
	return size_;
}

FloatCoord ComponentBase::getScaledPos()
{
	return nullPos_;
}

FloatCoord ComponentBase::getPos()
{
	return nullPos_;
}

void ComponentBase::normilizeNullCoords()
{
	nullPos_ = FloatCoord{ round(nullPos_.x * 10000) / 10000, round(nullPos_.y * 10000) / 10000 };
}


float ComponentBase::getScale()
{
	return scale_;
}

void ComponentBase::setScale(float scale)
{
	scale_ = scale;
}

FloatCoord ComponentBase::getScaledSIZE()
{
	return FloatCoord{ size_.x * scale_, size_.y * scale_ };
}

void ComponentBase::IncreaseScale(float value)
{
	if ((value > 0 && scale_ < 50.0) || (value < 0 && scale_ > 0.1))
		scale_ += value;
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
	setPos(obj.getScaledPos().x + (obj.getScaledSIZE().x - this->getScaledSIZE().x) / 2.0f, obj.getScaledPos().y + (obj.getScaledSIZE().y - this->getScaledSIZE().y) / 2.0f);
}

void ComponentBase::setPosRelativeTo(ComponentBase& obj, RelativeBindingType side, float offsetX, float offsetY)
{
	switch (side)
	{
	case RelativeBindingType::SIDE_LEFT:

		setPos(obj.getScaledPos().x - this->getScaledSIZE().x + offsetX, obj.getScaledPos().y + offsetY);
		break;

	case RelativeBindingType::SIDE_RIGHT:

		setPos(obj.getScaledPos().x + obj.getScaledSIZE().x + offsetX, obj.getScaledPos().y + offsetY);
		break;

	case RelativeBindingType::SIDE_TOP:

		setPos(obj.getScaledPos().x + offsetX, obj.getScaledPos().y + obj.getScaledSIZE().y + offsetY);
		break;

	case RelativeBindingType::SIDE_BOTTOM:

		setPos(obj.getScaledPos().x + offsetX, obj.getScaledPos().y - this->getScaledSIZE().y + offsetY);
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

bool ComponentBase::isMouseOn()
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

bool ComponentBase::isClickOn()
{
	if (isMouseOn() && px::isMouseLeftClick && !px::isMouseAlreadyUsed)
		return true;
	return false;
}

bool ComponentBase::isRectCollisionWith(ComponentBase& obj)
{
	bool collisionX = this->nullPos_.x + this->getScaledSIZE().x >= obj.nullPos_.x &&
		obj.nullPos_.x + obj.getScaledSIZE().x >= this->nullPos_.x;
	bool collisionY = this->nullPos_.y + this->getScaledSIZE().y >= obj.nullPos_.y &&
		obj.nullPos_.y + obj.getScaledSIZE().y >= this->nullPos_.y;
	return collisionX && collisionY;
}

bool ComponentBase::isRoundCollisionWith(ComponentBase& obj)
{
	glm::vec2 center(this->nullPos_.x + this->getScaledSIZE().x / 2, this->nullPos_.y + this->getScaledSIZE().y / 2);
	glm::vec2 aabb_half_extents(obj.getScaledSIZE().x / 2.0f, obj.getScaledSIZE().y / 2.0f);
	glm::vec2 aabb_center(
		obj.nullPos_.x + aabb_half_extents.x,
		obj.nullPos_.y + aabb_half_extents.y
	);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	return glm::length(difference) < this->nullPos_.x / 2;
}