#include "PixelEngine.h"
using namespace Px;


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(PxButton* self))
	: AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(btncallback);
}


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(PxButton* self))
	: AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(btncallback);
}

void PxButton::init(void (*btncallback)(PxButton* self))
{
	this->btncallback = btncallback;
}

void Px::PxButton::update()
{
	if (isClickOn())
	{
		this->btncallback(this);
	}
}