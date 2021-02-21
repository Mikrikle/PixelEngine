#include "PixelEngine.h"

int PxObj::WindowSizeX = 0;
int PxObj::WindowSizeY = 0;
bool PxObj::MouseLeftClick = false;
bool PxObj::MouseRightClick = false;

PxObj::PxObj(int ROWS, int COLS, int WindowWSizeX, int WindowSizeY, float WIDTH, float HEIGHT) : PixelCanvas(ROWS, COLS, WIDTH, HEIGHT), PixelArray(ROWS, COLS)
{
	PxObj::WindowSizeX = WindowWSizeX;
	PxObj::WindowSizeY = WindowSizeY;
	this->COLS = COLS;
	this->ROWS = ROWS;
	this->MousePosCol = 0;
	this->MousePosRow = 0;
}

void PxObj::draw()
{
	render(getCanvas());
}

void PxObj::TransformMouseXtoGrid(int x, int y)
{
	glm::vec2 absoluteMousePos = glm::vec2((x / ((float)PxObj::WindowSizeX / 2.0f)) - 1.0f, (((float)PxObj::WindowSizeY - y) / ((float)PxObj::WindowSizeY / 2)) - 1.0f);
	float realX = getNullPos().x - (getScale() - 1) * getWIDTH() / 2;
	float realY = getNullPos().y - (getScale() - 1) * getHEIGHT() / 2;

	if (absoluteMousePos.x > realX && absoluteMousePos.x < realX + getWIDTH()*getScale() &&
		absoluteMousePos.y > realY && absoluteMousePos.y < realY + getHEIGHT() * getScale())
	{
		MousePosCol = (absoluteMousePos.x - realX) * COLS / (getWIDTH()*getScale());
		MousePosRow = ROWS - ((absoluteMousePos.y - realY) * ROWS / (getHEIGHT()*getScale()));
	}
	else
	{
		MousePosCol = -1;
		MousePosRow = -1;
	}
}

