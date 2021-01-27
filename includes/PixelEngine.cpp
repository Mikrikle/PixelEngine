#include "../includes/PixelEngine.h"

bool PxEngine::MouseLeftClick = false;
bool PxEngine::MouseRightClick = false;
unsigned int PxEngine::WindowSizeX = 1;
unsigned int PxEngine::WindowSizeY = 1;

void PxEngine::initCanvases()
{
	pixelCanvases = new float* [layersNum];
	for (int i = 0; i < layersNum; i++)
	{
		pixelCanvases[i] = new float[SIZE];
		for (int elem = 0; elem < SIZE; elem++)
			pixelCanvases[i][elem] = 0.0f;
	}
	mixLayerCanvas = new float[SIZE];
	for (int elem = 0; elem < SIZE; elem++)
		mixLayerCanvas[elem] = 0.0f;
}

void PxEngine::deleteCanvases()
{
	for (int i = 0; i < layersNum; i++)
		delete[] pixelCanvases[i];
	delete[] pixelCanvases;
}

PxEngine::PxEngine(int ROWS, int COLS, unsigned int WindowSizeX, unsigned int WindowSizeY)
{
	PxEngine::WindowSizeX = WindowSizeX;
	PxEngine::WindowSizeY = WindowSizeY;
	this->MousePosCol = 0;
	this->MousePosRow = 0;
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->SIZE = COLS * ROWS * 3;
	this->currentCanvas = 0;
	this->layersNum = 1;
	initCanvases();
}

PxEngine::~PxEngine()
{
	deleteCanvases();
	delete[] mixLayerCanvas;
}

int PxEngine::getROWS()
{
	return ROWS;
}

int PxEngine::getCOLS()
{
	return COLS;
}

void PxEngine::addLayer()
{
	float** NewPixelCanvases = new float* [layersNum + 1];
	for (int i = 0; i < layersNum + 1; i++)
		NewPixelCanvases[i] = new float[SIZE];

	for (int i = 0; i < layersNum; i++)
		for (int elem = 0; elem < SIZE; elem++)
			NewPixelCanvases[i][elem] = pixelCanvases[i][elem];

	deleteCanvases();
	layersNum++;
	pixelCanvases = NewPixelCanvases;
}

int PxEngine::getCurrentLayer()
{
	return currentCanvas;
}

void PxEngine::setLayer(int value)
{
	if (value >= 0 && value < layersNum)
		currentCanvas = value;
}

float* PxEngine::getCanvas()
{
	return pixelCanvases[currentCanvas];
}

float* PxEngine::getMixLayerCanvas()
{
	for (int elem = 0; elem < SIZE; elem++)
		for (int i = 0; i < layersNum; i++)
			if (pixelCanvases[currentCanvas][elem] > mixLayerCanvas[elem])
				mixLayerCanvas[elem] = pixelCanvases[currentCanvas][elem];
	return mixLayerCanvas;
}

void PxEngine::setPixel(int i, int j, float r, float g, float b)
{
	if (i * (COLS * 3) + j * 3 + 3 <= SIZE && i * (COLS * 3) + j * 3 + 3 >= 0)
	{
		i = ROWS - i - 1;
		pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3] = r;
		pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3 + 1] = g;
		pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3 + 2] = b;
	}
}

void PxEngine::setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
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

int PxEngine::TransformMouseXtoCol(int MousePosX)
{
	if (MousePosX <= 0)
		return 0;
	else if (MousePosX >= PxEngine::WindowSizeX)
		return COLS - 1;

	return MousePosX / ((float)PxEngine::WindowSizeX / COLS);
}

int PxEngine::TransformMouseYtoRow(int MousePosY)
{
	if (MousePosY <= 0)
		return 0;
	else if (MousePosY >= PxEngine::WindowSizeY)
		return ROWS - 1;

	return MousePosY / ((float)PxEngine::WindowSizeY / COLS);
}