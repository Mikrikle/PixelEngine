#include "PixelEngine.h"
using namespace Px;


void AbstractRectangle::changeBackground(glm::mat4x3 color)
{
	genVAO(color, this->WIDTH, this->HEIGHT, 6);
}

void AbstractRectangle::changeBackground(glm::mat2x3 color)
{
	genVAO(color, this->WIDTH, this->HEIGHT, 12);
}

void AbstractRectangle::draw() 
{
	transform = glm::mat4(1.0f);
	shader->use();
	shader->setFloat("TextureOpacity", this->TextureOpacity);
	transform = glm::translatePos(transform, glm::vec3(translatePos.x, translatePos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	drawVAO();
}

AbstractRectangle::AbstractRectangle(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY)
	: AbstractRectangle(WIDTH, HEIGHT, shader, scale, posX, posY)
{
	genVAO(bgcolor, this->WIDTH, this->HEIGHT, 6);
}


AbstractRectangle::AbstractRectangle(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY)
	: AbstractRectangle(WIDTH, HEIGHT, shader, scale, posX, posY)
{
	genVAO(bgcolor, this->WIDTH, this->HEIGHT, 12);
}


AbstractRectangle::AbstractRectangle(float WIDTH, float HEIGHT, Shader* shader, float scale, float posX, float posY)
	: ComponentMovable(WIDTH * 2, HEIGHT * 2)
{
	this->shader = shader;
	genTexture();
	setScale(scale);
	setTranslate(posX, posY);
}
