#include "PixelEngine.h"
using namespace Px;


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)())
	: PxButton(WIDTH, HEIGHT, shader, scale, posX, posY, btncallback)
{
	genVAO(bgcolor, this->WIDTH, this->HEIGHT, 6);
}


PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)())
	: PxButton(WIDTH, HEIGHT, shader, scale, posX, posY, btncallback)
{
	genVAO(bgcolor, this->WIDTH, this->HEIGHT, 12);
}


PxButton::PxButton(float WIDTH, float HEIGHT, Shader* shader, float scale, float posX, float posY, void (*btncallback)())
	: ComponentMovable(WIDTH * 2, HEIGHT * 2)
{
	this->shader = shader;
	genTexture();
	setScale(scale);
	setTranslate(posX, posY);
	this->btncallback = btncallback;
}


void PxButton::changeBackground(glm::mat4x3 color)
{
	genVAO(color, WIDTH, HEIGHT, 6);
}


void PxButton::changeBackground(glm::mat2x3 color)
{
	genVAO(color, WIDTH, HEIGHT, 12);
}


void PxButton::draw()
{
	transform = glm::mat4(1.0f);
	shader->use();
	shader->setFloat("TextureOpacity", 1.0f);
	transform = glm::translatePos(transform, glm::vec3(translatePos.x, translatePos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	drawVAO();
}


void PxButton::eventProcessing(float deltaTime)
{
	if (IsLocatedOnObject(Px::MousePosX, Px::MousePosY) && Px::MouseLeftClick)
	{
		btncallback();
		Px::MouseLeftClick = false;
	}
}