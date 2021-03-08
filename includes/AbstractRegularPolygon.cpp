#include "PixelEngine.h"
using namespace Px;


void AbstractRegularPolygon::changeBackground(glm::mat2x3 color)
{
	genVAO(color, this->SIZE.x, this->vertices_count);
}

void AbstractRegularPolygon::draw()
{
	transform = glm::mat4(1.0f);
	shader->use();
	shader->setFloat("TextureOpacity", this->TextureOpacity);
	transform = glm::translatePos(transform, glm::vec3(translatePos.x, translatePos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	drawVAO();
}

AbstractRegularPolygon::AbstractRegularPolygon(float radius, float vertices_count, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY)
	: ComponentBase(radius * 2, radius * 2)
{
	this->vertices_count = vertices_count;
	this->shader = shader;
	genTexture();
	setScale(scale);
	setPos(posX, posY);
	genVAO(bgcolor, this->SIZE.x, this->vertices_count);
}