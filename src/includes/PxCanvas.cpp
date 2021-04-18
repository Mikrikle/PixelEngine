#include "PixelEngine.h"
using namespace px;

PxCanvas::PxCanvas(int rows, int cols, float width, float height, float scale, float posX, float posY, Shader* shader) :
	AbstractRectangle(width, height, shader)
{
	setScale(scale);
	setPos(posX, posY);
	rows_ = rows;
	cols_ = cols;
	pixelCanvas_.resize(static_cast<size_t>(cols_ * rows_ * 3), 0.0f);
	mousePosCol_ = 0;
	mousePosRow_ = 0;
	genTexture();
}

PxCanvas::~PxCanvas()
{
}

void PxCanvas::draw()
{
	setTexture(pixelCanvas_.data(), rows_, cols_);
	this->AbstractRectangle::draw();
}

void px::PxCanvas::update()
{
	if (isMouseOn())
	{
		mousePosCol_ = static_cast<int>((px::absoluteMousePosX - nullPos_.x) * getCols() / (getSIZE().x * getScale()));
		mousePosRow_ = static_cast<int>(getRows() - ((px::absoluteMousePosY - nullPos_.y) * getRows() / (getSIZE().y * getScale())));
	}
	else
	{
		mousePosCol_ = -1;
		mousePosRow_ = -1;
	}
}

glm::vec3 PxCanvas::getPixel()
{
	return getPixel(mousePosRow_, mousePosCol_);
}

glm::vec3 PxCanvas::getPixel(int row, int col)
{
	if (row >= 0 && col >= 0 && row <= rows_ && col < cols_)
	{
		int pos = (rows_ - row - 1) * (cols_ * 3) + (col * 3);
		if (pos + 2 < pixelCanvas_.size())
		{
			return glm::vec3(pixelCanvas_[pos], pixelCanvas_[pos + 1], pixelCanvas_[pos + 2]);
		}
	}
	return glm::vec3(0, 0, 0);
}

int PxCanvas::getRows()
{
	return rows_;
}

int PxCanvas::getCols()
{
	return cols_;
}

int PxCanvas::getMouseCol()
{
	return mousePosCol_;
}

int PxCanvas::getMouseRow()
{
	return mousePosRow_;
}

void PxCanvas::setPixel(int i, int j, float r, float g, float b)
{
	if (i >= 0 && j >= 0 && i <= rows_ && j < cols_)
	{
		int pos = (rows_ - i - 1) * (cols_ * 3) + (j * 3);
		if (pos + 2 < pixelCanvas_.size())
		{
			pixelCanvas_[pos] = r;
			pixelCanvas_[pos + 1] = g;
			pixelCanvas_[pos + 2] = b;
		}
	}
}

void PxCanvas::setPixel_unsafety(int i, int j, float r, float g, float b)
{
	int pos = (rows_ - i - 1) * (cols_ * 3) + (j * 3);
	pixelCanvas_[pos] = r;
	pixelCanvas_[pos + 1] = g;
	pixelCanvas_[pos + 2] = b;
}

void PxCanvas::setPixel(float r, float g, float b)
{
	setPixel(mousePosRow_, mousePosCol_, r, g, b);
}

void PxCanvas::setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
{
	if (i >= 0 && j >= 0 && end_i >= 0 && end_j >= 0)
	{
		glm::vec2 move = glm::vec2(i - end_i, j - end_j);
		double len = glm::length(move);
		double stepi = move.x / len;
		double stepj = move.y / len;
		for (int brushi = -width / 2; brushi <= width / 2; ++brushi)
		{
			for (int brushj = -width / 2; brushj <= width / 2; ++brushj)
			{
				for (int k = 0; k < ceil(len); k++)
				{
					setPixel(end_i + static_cast<int>(stepi * k) + brushi, end_j + static_cast<int>(stepj * k) + brushj, r, g, b);
				}
			}
		}
	}
}

void PxCanvas::fillBlack()
{
	std::fill(pixelCanvas_.begin(), pixelCanvas_.end(), 0.0f);
}

void PxCanvas::fillWhite()
{
	std::fill(pixelCanvas_.begin(), pixelCanvas_.end(), 1.0f);
}