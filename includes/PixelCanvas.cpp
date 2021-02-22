#include "PixelEngine.h"

int PixelCanvas::WindowSizeX = 0;
int PixelCanvas::WindowSizeY = 0;
bool PixelCanvas::MouseLeftClick = false;
bool PixelCanvas::MouseRightClick = false;


PixelCanvas::PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, int WindowSizeX, int WindowSizeY) : PixelCanvas::PixelCanvas(ROWS, COLS, WIDTH, HEIGHT)
{
	PixelCanvas::WindowSizeX = WindowSizeX;
	PixelCanvas::WindowSizeY = WindowSizeY;
}

PixelCanvas::PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT) : PxCanvasObj(ROWS, COLS, WIDTH, HEIGHT), PixelArray(ROWS, COLS)
{
	this->COLS = COLS;
	this->ROWS = ROWS;
	this->MousePosCol = 0;
	this->MousePosRow = 0;
}

void PixelCanvas::draw()
{
	render(getCanvas());
}

void PixelCanvas::TransformMousePosToGrid(int x, int y)
{
	glm::vec2 absoluteMousePos = glm::vec2((x / ((float)PixelCanvas::WindowSizeX / 2.0f)) - 1.0f, (((float)PixelCanvas::WindowSizeY - y) / ((float)PixelCanvas::WindowSizeY / 2)) - 1.0f);
	float realX = getNullPos().x - (getScale() - 1) * getWIDTH() / 2;
	float realY = getNullPos().y - (getScale() - 1) * getHEIGHT() / 2;

	if (absoluteMousePos.x > realX && absoluteMousePos.x < realX + getWIDTH() * getScale() &&
		absoluteMousePos.y > realY && absoluteMousePos.y < realY + getHEIGHT() * getScale())
	{
		MousePosCol = (absoluteMousePos.x - realX) * COLS / (getWIDTH() * getScale());
		MousePosRow = ROWS - ((absoluteMousePos.y - realY) * ROWS / (getHEIGHT() * getScale()));
	}
	else
	{
		MousePosCol = -1;
		MousePosRow = -1;
	}
}

