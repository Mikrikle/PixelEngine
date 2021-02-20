#include "../includes/PixelEngine.h"

PixelArray::PixelArray(int ROWS, int COLS)
{
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->SIZE = COLS * ROWS * 3;
	pixelCanvas = new float[SIZE];
	for (int elem = 0; elem < SIZE; elem++)
		pixelCanvas[elem] = 0.0f;
}

PixelArray::~PixelArray()
{
	delete[] pixelCanvas;
}

int PixelArray::getROWS()
{
	return ROWS;
}

int PixelArray::getCOLS()
{
	return COLS;
}

float* PixelArray::getCanvas()
{
	return pixelCanvas;
}

void PixelArray::setPixel(int i, int j, float r, float g, float b)
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

void PixelArray::setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
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

void PixelArray::clear()
{
	for (int i = 0; i < SIZE; i++)
		pixelCanvas[i] = 0.0f;
}