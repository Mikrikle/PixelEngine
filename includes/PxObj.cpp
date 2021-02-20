#include "PixelEngine.h"

int PxObj::WindowSizeX = 0;
int PxObj::WindowSizeY = 0;
bool PxObj::MouseLeftClick = false;
bool PxObj::MouseRightClick = false;

PxObj::PxObj(int ROWS, int COLS, int width, int height) : PixelCanvas(ROWS, COLS), PixelArray(ROWS, COLS)
{
	PxObj::WindowSizeX = width;
	PxObj::WindowSizeY = height;
	this->COLS = COLS;
	this->ROWS = ROWS;
	this->MousePosCol = 0;
	this->MousePosRow = 0;
}

void PxObj::draw()
{
	render(getCanvas());
}

void PxObj::TransformMouseXtoCol(int x)
{
	int realMousePos = x / getScale() + PxObj::WindowSizeX / 2.0 / getScale() * ((double)getScale() - 1) - (PxObj::WindowSizeX / 2.0 * getTx());
	int col = realMousePos / ((float)PxObj::WindowSizeX / COLS);
	if (col >= 0 && col < COLS)
		this->MousePosCol = col;
	else
		this->MousePosCol = -1;
}

void PxObj::TransformMouseYtoRow(int y)
{
	int realMousePos = y / getScale() + PxObj::WindowSizeY / 2.0 / getScale() * ((double)getScale() - 1) + (PxObj::WindowSizeY / 2.0 * getTy());
	int row = realMousePos / ((float)PxObj::WindowSizeY / ROWS);
	if (row >= 0 && row < ROWS)
		this->MousePosRow = row;
	else
		this->MousePosRow = -1;
}