#include "PixelEngine.h"
using namespace Px;

void VAOrectangle::genVAO(glm::mat4x3 color, float WIDTH, float HEIGHT, int indicesSize)
{
	this->indicesSize = indicesSize;
	GLfloat vertices[] = {
	WIDTH / 2.0f,  HEIGHT / 2.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
	WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f,   color[1].x, color[1].y, color[1].z, 1.0f, 0.0f,
   -WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f,   color[2].x, color[2].y, color[2].z, 0.0f, 0.0f,
   -WIDTH / 2.0f,  HEIGHT / 2.0f, 0.0f,   color[3].x, color[3].y, color[3].z, 0.0f, 1.0f,
	};
	genBuffers(vertices, sizeof(vertices), indices2triangles, sizeof(indices2triangles));
}

void VAOrectangle::genVAO(glm::mat2x3 color, float WIDTH, float HEIGHT, int indicesSize)
{
	this->indicesSize = indicesSize;
	GLfloat vertices[] = {
	WIDTH / 2.0f,  HEIGHT / 2.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
	WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 0.0f,
   -WIDTH / 2.0f, -HEIGHT / 2.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 0.0f, 0.0f,
   -WIDTH / 2.0f,  HEIGHT / 2.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,                   color[1].x, color[1].y, color[1].z, 0.5f, 0.5f,
	};
	genBuffers(vertices, sizeof(vertices), indices4triangles, sizeof(indices4triangles));
}

void VAOrectangle::drawVAO()
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indicesSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}