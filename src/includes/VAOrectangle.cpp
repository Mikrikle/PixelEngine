#include "PixelEngine.h"
using namespace px;
using namespace engine;

void VAOrectangle::genVAO(glm::mat4x3 color, float width, float height)
{
	this->indicesSize_ = 6;
	GLfloat vertices[] = {
		width,  height, 0.0f,		color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
		width, 0, 0.0f,				color[1].x, color[1].y, color[1].z, 1.0f, 0.0f,
		0, 0, 0.0f,					color[2].x, color[2].y, color[2].z, 0.0f, 0.0f,
		0,  height, 0.0f,			color[3].x, color[3].y, color[3].z, 0.0f, 1.0f,
	};
	genBuffers(vertices, sizeof(vertices), indices2triangles, sizeof(indices2triangles));
}

void VAOrectangle::genVAO(glm::mat2x3 color, float width, float height)
{
	this->indicesSize_ = 12;
	GLfloat vertices[] = {
		width,  height, 0.0f,				color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
		width, 0, 0.0f,						color[0].x, color[0].y, color[0].z, 1.0f, 0.0f,
		0, 0, 0.0f,							color[0].x, color[0].y, color[0].z, 0.0f, 0.0f,
		0,  height, 0.0f,					color[0].x, color[0].y, color[0].z, 0.0f, 1.0f,
		width / 2.0f, height / 2.0f, 0.0f,  color[1].x, color[1].y, color[1].z, 0.5f, 0.5f,
	};

	genBuffers(vertices, sizeof(vertices), indices4triangles, sizeof(indices4triangles));
}

void VAOrectangle::genVAO(glm::vec3 color, float width, float height)
{
	glm::mat4x3 new_color = glm::mat4x3(color, color, color, color);
	genVAO(new_color, width, height);
}

void VAOrectangle::genVAO(float r, float g, float b, float width, float height)
{
	glm::vec3 rgb(r, g, b);
	glm::mat4x3 new_color = glm::mat4x3(rgb, rgb, rgb, rgb);
	genVAO(new_color, width, height);
}

void VAOrectangle::drawVAO()
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indicesSize_, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}