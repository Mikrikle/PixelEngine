#include "PixelEngine.h"
using namespace Px;

VAOregularPolygon::~VAOregularPolygon()
{
	delete[] indices;
}

void VAOregularPolygon::genVAO(glm::mat2x3 color, float radius, int vertices_count)
{
	verticesNumber = vertices_count;
	if (verticesNumber > 360)
	{
		verticesNumber = 360;
	}
	else if (verticesNumber < 3)
	{
		verticesNumber = 3;
	}
	GLfloat* vertices = new GLfloat[verticesNumber * 9];
	this->indices = new GLuint[verticesNumber * 3];
	GLfloat alpha = 360.0f / verticesNumber;
	vertices[0] = vertices[1] = vertices[2] = 0.0f;
	vertices[3] = color[0].x;
	vertices[4] = color[0].y;
	vertices[5] = color[0].z;
	for (GLuint line = 1; line <= verticesNumber; line++)
	{
		vertices[0 + 6 * line] = (GLfloat)(sin(glm::radians(alpha * line)) * radius);
		vertices[1 + 6 * line] = (GLfloat)(cos(glm::radians(alpha * line)) * radius);
		vertices[2 + 6 * line] = 0.0f;
		vertices[3 + 6 * line] = color[1].x;
		vertices[4 + 6 * line] = color[1].y;
		vertices[5 + 6 * line] = color[1].z;
	}
	for (GLuint i = 0, k = 1; i < verticesNumber * 3; i += 3, k++)
	{
		indices[0 + i] = 0;
		indices[1 + i] = k;
		indices[2 + i] = k % verticesNumber + 1;
	}
	this->indicesSize = sizeof(indices[0]) * verticesNumber * 3;
	genBuffers(vertices, sizeof(vertices[0]) * verticesNumber * 8, indices, this->indicesSize, false);
	delete[] vertices;
}


void VAOregularPolygon::drawVAO()
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->verticesNumber * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}