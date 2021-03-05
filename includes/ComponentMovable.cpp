#include "PixelEngine.h"
using namespace Px;

ComponentMovable::ComponentMovable(float WIDTH, float HEIGHT) : ComponentBase(WIDTH, HEIGHT)
{
	this->scale = 1.0f;
	this->nullPos = FloatCoord{ -WIDTH / 2.0f, -HEIGHT / 2.0f };
	this->translatePos = FloatCoord{ 0.0f , 0.0f };
	this->absoluteMousePos = FloatCoord{ -1.0f , -1.0f };
	this->realPos = FloatCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };
	this->transform = glm::mat4(1.0f);
}

FloatCoord ComponentMovable::getNullPos()
{
	return nullPos;
}

void ComponentMovable::normilizeNullCoords()
{
	nullPos = FloatCoord{ round(nullPos.x * 10000) / 10000, round(nullPos.y * 10000) / 10000 };
}

float ComponentMovable::getScale()
{
	return scale;
}

void ComponentMovable::setScale(float scale)
{
	this->scale = scale;
}

FloatCoord ComponentMovable::getScaledSIZE()
{
	return FloatCoord{ WIDTH * scale, HEIGHT * scale };
}

void ComponentMovable::increaseScale(float value)
{
	if ((value > 0 && scale < 50.0) || (value < 0 && scale > 0.1))
		this->scale += value;
}

void ComponentMovable::setTranslate(float x, float y)
{
	nullPos = FloatCoord{ -WIDTH / 2.0f + x, -HEIGHT / 2.0f + y };
	translatePos = FloatCoord{ x, y };
	normilizeNullCoords();
}

void ComponentMovable::increaseTranslate(float moveX, float moveY)
{
	nullPos = FloatCoord{ nullPos.x += moveX, nullPos.y += moveY };
	translatePos.x += moveX;
	translatePos.y += moveY;
	normilizeNullCoords();
}

bool ComponentMovable::IsLocatedOnObject(int x, int y)
{
	if (x >= 0 && x <= Px::WindowSizeX && y >= 0 && y <= Px::WindowSizeY)
	{
		absoluteMousePos = FloatCoord{ (x / ((float)Px::WindowSizeX / 2.0f)) - 1.0f, (((float)Px::WindowSizeY - y) / ((float)Px::WindowSizeY / 2)) - 1.0f };
		realPos = FloatCoord{ nullPos.x - (scale - 1) * WIDTH / 2 , nullPos.y - (scale - 1) * HEIGHT / 2 };

		if (absoluteMousePos.x > realPos.x && absoluteMousePos.x < realPos.x + getScaledSIZE().x &&
			absoluteMousePos.y > realPos.y && absoluteMousePos.y < realPos.y + getScaledSIZE().y)
		{
			return true;
		}
	}
	return false;
}

bool ComponentMovable::isRectCollisionWith(ComponentMovable& obj)
{
	bool collisionX = this->realPos.x + this->getScaledSIZE().x >= obj.realPos.x &&
		obj.getScaledSIZE().x + obj.realPos.x >= this->realPos.x;

	bool collisionY = this->realPos.y + this->getScaledSIZE().y >= obj.realPos.y &&
		obj.realPos.y + obj.getScaledSIZE().y >= this->realPos.y;

	return collisionX && collisionY;
}

bool ComponentMovable::isRoundCollisionWith(ComponentMovable& obj)
{
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