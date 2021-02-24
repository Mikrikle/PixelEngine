#include "PixelEngine.h"
using namespace Px;

PxButton::PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(ComponentMovable& obj), ComponentMovable& obj)
	: ComponentMovable(WIDTH, HEIGHT)
{
	this->bindObj = &obj;
	this->shader = shader;
	genBackground(bgcolor, WIDTH*2.0, HEIGHT*2.0);
	genTexture();
	setScale(scale);
	setTranslate(posX, posY);
	this->btncallback = btncallback;
	
}

void PxButton::changeBackground(glm::mat4x3 color)
{
	genBackground(color, WIDTH, HEIGHT);
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
	if (isClickOn(Px::MousePosX, Px::MousePosY) && Px::MouseLeftClick)
	{
		btncallback(*bindObj);
		Px::MouseLeftClick = false;
	}
}