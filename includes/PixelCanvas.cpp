#include "../includes/PixelEngine.h"


void PixelCanvas::initCanvas(glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY)
{
	initCanvas(bgcolor, shader);
	setScale(scale);
	setTranslate(posX, posY);
}

void PixelCanvas::initCanvas(glm::mat4x3 bgcolor, Shader* shader)
{
	this->shader = shader;
	genCanvas(bgcolor);
	genTexture();
}

PixelCanvas::PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT)
{
	this->shader = nullptr;
	this->TextureOpacity = 0.5f;
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->transform = glm::mat4(1.0f);
	this->scale = 1.0f;
	this->TEXTURE = 0;
	this->VAO = 0;
	this->WIDTH = WIDTH * 2.0;
	this->HEIGHT = HEIGHT * 2.0;
	this->nullPos = PxCoord{ -WIDTH / 2.0f, -HEIGHT / 2.0f };
	this->translatePos = PxCoord{ 0.0f , 0.0f };
}

PixelCanvas::~PixelCanvas()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void PixelCanvas::changeBackground(glm::mat4x3 color)
{
	genCanvas(color);
}

void PixelCanvas::setOpacity(float value)
{
	if (value >= 0.0 && value <= 1.0)
		this->TextureOpacity = value;
}

void PixelCanvas::render(float* canvas)
{
	transform = glm::mat4(1.0f);
	setPixelTexture(canvas);
	shader->use();
	shader->setFloat("TextureOpacity", this->TextureOpacity);
	transform = glm::translatePos(transform, glm::vec3(translatePos.x, translatePos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void PixelCanvas::normilizeNullCoords()
{
	nullPos = PxCoord{ round(nullPos.x * 100) / 100, round(nullPos.y * 100) / 100 };
}

float PixelCanvas::getScale()
{
	return scale;
}

void PixelCanvas::setScale(float scale)
{
	this->scale = scale;
}

void PixelCanvas::increaseScale(float value)
{
	if ((value > 0 && scale < 50.0) || (value < 0 && scale > 0.1))
		this->scale += value;
}

void PixelCanvas::setTranslate(float x, float y)
{
	nullPos = PxCoord{ -WIDTH / 2.0f + x, -HEIGHT / 2.0f + y };
	translatePos = PxCoord{ x, y };
	normilizeNullCoords();
}

void PixelCanvas::increaseTranslate(float moveX, float moveY)
{
	nullPos = PxCoord{ nullPos.x += moveX, nullPos.y += moveY };
	translatePos.x += moveX;
	translatePos.y += moveY;
	normilizeNullCoords();
}

float PixelCanvas::getWIDTH()
{
	return WIDTH;
}

float PixelCanvas::getHEIGHT()
{
	return HEIGHT;
}

PxCoord PixelCanvas::getNullPos()
{
	return nullPos;
}

void PixelCanvas::genCanvas(glm::mat4x3 color)
{
	GLfloat vertices[] = {
		WIDTH / 2.0,  HEIGHT / 2.0, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
		WIDTH / 2.0, -HEIGHT / 2.0, 0.0f,   color[1].x, color[1].y, color[1].z, 1.0f, 0.0f,
	   -WIDTH / 2.0, -HEIGHT / 2.0, 0.0f,   color[2].x, color[2].y, color[2].z, 0.0f, 0.0f,
	   -WIDTH / 2.0,  HEIGHT / 2.0, 0.0f,   color[3].x, color[3].y, color[3].z, 0.0f, 1.0f,
	};
	genBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
}

void PixelCanvas::genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI)
{
	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeV, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeI, indices, GL_STATIC_DRAW);
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
}

void PixelCanvas::genTexture()
{
	glGenTextures(1, &this->TEXTURE);
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void PixelCanvas::setPixelTexture(float* canvas)
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, canvas);
}
