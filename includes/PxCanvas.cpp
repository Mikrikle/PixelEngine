#include "../includes/PixelEngine.h"
using namespace Px;

PxCanvas::PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(ROWS, COLS);
}

PxCanvas::PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init(ROWS, COLS);
}

void PxCanvas::init(int ROWS, int COLS)
{
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->SIZE = COLS * ROWS * 3;
	this->pixelCanvas = new float[SIZE];
	for (int elem = 0; elem < SIZE; elem++)
		this->pixelCanvas[elem] = 0.0f;
	this->MousePosCol = 0;
	this->MousePosRow = 0;
	genTexture();
}

PxCanvas::~PxCanvas()
{
	delete[] pixelCanvas;
}

void PxCanvas::draw()
{
	setTexture(this->pixelCanvas, this->ROWS, this->COLS);
	this->AbstractRectangle::draw();
}

void Px::PxCanvas::update()
{
	if (isMouseOn())
	{
		MousePosCol = (Px::absoluteMousePosX - realPos.x) * getCOLS() / (getSIZE().x * getScale());
		MousePosRow = getROWS() - ((Px::absoluteMousePosY - realPos.y) * getROWS() / (getSIZE().y * getScale()));
	}
	else
	{
		MousePosCol = -1;
		MousePosRow = -1;
	}
}

int PxCanvas::getROWS()
{
	return ROWS;
}

int PxCanvas::getCOLS()
{
	return COLS;
}

int PxCanvas::getMouseCol()
{
	return MousePosCol;
}

int PxCanvas::getMouseRow()
{
	return MousePosRow;
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
		this->pixelCanvas[i] = 0.0f;
}