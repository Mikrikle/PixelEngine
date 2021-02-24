#include "PixelEngine.h"
using namespace Px;

PxStaticBackground::PxStaticBackground(glm::mat4x3 color, Shader* shader) : ComponentBase(2.0f, 2.0f)
{
	this->shader = shader;
}

void PxStaticBackground::changeBackground(glm::mat4x3 color)
{
	genBackground(color, 2.0f, 2.0f);
}

void PxStaticBackground::draw()
{
	glm::mat4 transform = glm::mat4(1.0f);
	shader->use();
	shader->setFloat("TextureOpacity", 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	drawVAO();
}