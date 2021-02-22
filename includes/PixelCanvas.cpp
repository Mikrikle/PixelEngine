#include "PixelEngine.h"

PixelCanvas::PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, int WindowSizeX, int WindowSizeY) : PixelCanvas::PixelCanvas(ROWS, COLS, WIDTH, HEIGHT)
{
	Px::WindowSizeX = WindowSizeX;
	Px::WindowSizeY = WindowSizeY;
}

PixelCanvas::PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT) : PxCanvasObj(ROWS, COLS, WIDTH, HEIGHT)
{
	this->MousePosCol = 0;
	this->MousePosRow = 0;
}

void PixelCanvas::draw()
{
	render();
}

void PixelCanvas::TransformMousePosToGrid(int x, int y)
{

	if (isClickOn(x, y))
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

