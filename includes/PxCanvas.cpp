#include "../includes/PixelEngine.h"
using namespace Px;

PxCanvas::PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	PxCanvas(ROWS, COLS, WIDTH, HEIGHT, bgcolor, shader)
{
	setScale(scale);
	setTranslate(posX, posY);
}

PxCanvas::PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader) :
	ComponentMovable(WIDTH, HEIGHT)
{
	this->shader = shader;
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->transform = glm::mat4(1.0f);
	this->SIZE = COLS * ROWS * 3;
	this->pixelCanvas = new float[SIZE];
	this->MousePosCol = 0;
	this->MousePosRow = 0;
	for (int elem = 0; elem < SIZE; elem++)
		this->pixelCanvas[elem] = 0.0f;
	genBackground(bgcolor, WIDTH, HEIGHT);
	genTexture();
}

PxCanvas::~PxCanvas()
{
	delete[] pixelCanvas;
}

void PxCanvas::changeBackground(glm::mat4x3 color)
{
	genBackground(color, WIDTH, HEIGHT);
}

void PxCanvas::draw()
{
	transform = glm::mat4(1.0f);
	setPixelTexture();
	shader->use();
	shader->setFloat("TextureOpacity", this->TextureOpacity);
	transform = glm::translatePos(transform, glm::vec3(translatePos.x, translatePos.y, 0.0f));
	transform = glm::scale(transform, glm::vec3(scale, scale, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	drawVAO();
}

void PxCanvas::setPixelTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, this->pixelCanvas);
}

int PxCanvas::getROWS()
{
	return ROWS;
}

int PxCanvas::getCOLS()
{
	return COLS;
}

void PxCanvas::setPixel(int i, int j, float r, float g, float b)
{
	if (i >= 0 && j >= 0)
	{
		if (i * (COLS * 3) + j * 3 + 3 <= SIZE && i * (COLS * 3) + j * 3 + 3 >= 0)
		{
			i = ROWS - i - 1;
			pixelCanvas[i * (COLS * 3) + j * 3] = r;
			pixelCanvas[i * (COLS * 3) + j * 3 + 1] = g;
			pixelCanvas[i * (COLS * 3) + j * 3 + 2] = b;
		}
	}
}

void PxCanvas::setPixel(float r, float g, float b)
{
	setPixel(MousePosRow, MousePosCol, r, g, b);
}

void PxCanvas::setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
{
	glm::vec2 move = glm::vec2(i - end_i, j - end_j);
	double len = glm::length(move);
	double stepi = move.x / len;
	double stepj = move.y / len;
	for (int brushi = -width / 2; brushi <= width / 2; brushi++)
	{
		for (int brushj = -width / 2; brushj <= width / 2; brushj++)
		{
			for (int k = 0; k < (int)ceil(len); k++)
			{
				setPixel(end_i + (stepi * k) + brushi, end_j + (stepj * k) + brushj, r, g, b);
			}
		}
	}
}

void PxCanvas::clear()
{
	for (int i = 0; i < SIZE; i++)
		pixelCanvas[i] = 0.0f;
}

void PxCanvas::eventProcessing(float deltaTime)
{
	if (baseMoveMod != Px::STATIC)
	{
		if (baseMoveMod == Px::MOVABLE || baseMoveMod == Px::FULL)
		{
			if (Px::Keys[68])
				increaseTranslate(0.1f * deltaTime * moveSpeed, 0.0f);
			if (Px::Keys[65])
				increaseTranslate(-0.1f * deltaTime * moveSpeed, 0.0f);
			if (Px::Keys[87])
				increaseTranslate(0.0f, 0.1f * deltaTime * moveSpeed);
			if (Px::Keys[83])
				increaseTranslate(0.0f, -0.1f * deltaTime * moveSpeed);
		}
		if (baseMoveMod == Px::SCALED || baseMoveMod == Px::FULL)
		{
			if ((Px::ScrollY > 0 && getScale() < 10.0) || (Px::ScrollY < 0 && getScale() > 0.4))
				increaseScale(Px::ScrollY / 4.0f * deltaTime * moveSpeed);
			Px::ScrollX = 0.0f;
			Px::ScrollY = 0.0f;
		}
	}

	if (isClickOn(Px::MousePosX, Px::MousePosY))
	{
		MousePosCol = (absoluteMousePos.x - realPos.x) * getCOLS() / (getWIDTH() * getScale());
		MousePosRow = getROWS() - ((absoluteMousePos.y - realPos.y) * getROWS() / (getHEIGHT() * getScale()));
	}
	else
	{
		MousePosCol = -1;
		MousePosRow = -1;
	}

}