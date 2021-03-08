#include "PixelEngine.h"
using namespace Px;

ComponentBase::ComponentBase(float WIDTH, float HEIGHT)
{
	this->SIZE = FloatCoord{ WIDTH, HEIGHT };
	this->scale = 1.0f;
	this->nullPos = FloatCoord{ -WIDTH / 2.0f, -HEIGHT / 2.0f };
	this->translatePos = FloatCoord{ 0.0f , 0.0f };
	this->realPos = FloatCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };
	this->transform = glm::mat4(1.0f);
	normilizeNullCoords();
}


FloatCoord ComponentBase::getSIZE()
{
	return SIZE;
}

FloatCoord ComponentBase::getScaledPos()
{
	this->realPos = FloatCoord{ nullPos.x - (scale - 1) * SIZE.x / 2 , nullPos.y - (scale - 1) * SIZE.y / 2 };
	return realPos;
}

FloatCoord ComponentBase::getPos()
{
	return translatePos;
}

void ComponentBase::normilizeNullCoords()
{
	nullPos = FloatCoord{ round(nullPos.x * 10000) / 10000, round(nullPos.y * 10000) / 10000 };
}

void ComponentBase::updateRealPos()
{
	this->realPos = FloatCoord{ nullPos.x - (scale - 1) * SIZE.x / 2 , nullPos.y - (scale - 1) * SIZE.y / 2 };
}

float ComponentBase::getScale()
{
	return scale;
}

void ComponentBase::setScale(float scale)
{
	this->scale = scale;
}

FloatCoord ComponentBase::getScaledSIZE()
{
	return FloatCoord{ SIZE.x * scale, SIZE.y * scale };
}

void ComponentBase::changeScale(float value)
{
	if ((value > 0 && scale < 50.0) || (value < 0 && scale > 0.1))
		this->scale += value;
}

void ComponentBase::setPos(float x, float y)
{
	nullPos = FloatCoord{ -SIZE.x / 2.0f + x, -SIZE.y / 2.0f + y };
	translatePos = FloatCoord{ x, y };
	normilizeNullCoords();
}

void ComponentBase::changePos(float moveX, float moveY)
{
	nullPos = FloatCoord{ nullPos.x += moveX, nullPos.y += moveY };
	translatePos.x += moveX;
	translatePos.y += moveY;
	normilizeNullCoords();
}

bool ComponentBase::isMouseOn()
{
	if (Px::MousePosX >= 0 && Px::MousePosX <= Px::WindowSizeX && Px::MousePosY >= 0 && Px::MousePosY <= Px::WindowSizeY)
	{
		updateRealPos();

		if (Px::absoluteMousePosX > realPos.x && Px::absoluteMousePosX  < realPos.x + getScaledSIZE().x &&
			Px::absoluteMousePosY > realPos.y && Px::absoluteMousePosY < realPos.y + getScaledSIZE().y)
		{
			return true;
		}
	}
	return false;
}

bool ComponentBase::isClickOn()
{
	if (isMouseOn() && Px::MouseLeftClick)
		return true;
	return false;
}

bool ComponentBase::isRectCollisionWith(ComponentBase& obj)
{
	this->updateRealPos();
	obj.updateRealPos();
	bool collisionX = this->realPos.x + this->getScaledSIZE().x >= obj.realPos.x &&
		obj.realPos.x + obj.getScaledSIZE().x >= this->realPos.x;
	bool collisionY = this->realPos.y + this->getScaledSIZE().y >= obj.realPos.y &&
		obj.realPos.y + obj.getScaledSIZE().y >= this->realPos.y;
	return collisionX && collisionY;
}

bool ComponentBase::isRoundCollisionWith(ComponentBase& obj)
{
	this->updateRealPos();
	obj.updateRealPos();
	glm::vec2 center(this->realPos.x + this->getScaledSIZE().x / 2, this->realPos.y + this->getScaledSIZE().y / 2);
	glm::vec2 aabb_half_extents(obj.getScaledSIZE().x / 2.0f, obj.getScaledSIZE().y / 2.0f);
	glm::vec2 aabb_center(
		obj.realPos.x + aabb_half_extents.x,
		obj.realPos.y + aabb_half_extents.y
	);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;
	return glm::length(difference) < this->realPos.x / 2;
}