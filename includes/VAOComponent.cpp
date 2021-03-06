#include "PixelEngine.h"
using namespace Px;


void VAOComponent::setOpacity(float value)
{
	if (value >= 0.0 && value <= 1.0)
		this->TextureOpacity = value;
}

VAOComponent::VAOComponent()
{
	this->TEXTURE = 0;
	this->VAO = 0;
	this->TextureOpacity = 0.5f;
	this->shader = nullptr;
	this->indicesSize = 0;
}

VAOComponent::~VAOComponent()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void VAOComponent::genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI)
{
	GLuint VBO, EBO;
	glDeleteVertexArrays(1, &this->VAO);
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeV, vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeI, indices, GL_DYNAMIC_DRAW);
	// coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void VAOComponent::genTexture()
{
	glGenTextures(1, &this->TEXTURE);
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void VAOComponent::setTexture(float* pixels, int ROWS, int COLS)
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, pixels);
}

void VAOComponent::setBaseColor(float r, float g, float b)
{
	float pixels[3]{ r ,g ,b };
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, pixels);
}