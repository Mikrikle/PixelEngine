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

int PxCanvas::transformPercentsToCoordX(float absolute_x)
{
	return static_cast<int>((absolute_x - nullPos_.x) * getCols() / (getSIZE().x * getScale()));
}

int PxCanvas::transformPercentsToCoordY(float absolute_y)
{
	return static_cast<int>(getRows() - ((absolute_y - nullPos_.y) * getRows() / (getSIZE().y * getScale())));
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
		mousePosCol_ = transformPercentsToCoordX(px::absoluteMousePosX);
		mousePosRow_ = transformPercentsToCoordY(px::absoluteMousePosY);
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

void PxCanvas::setPixel(int x, int y, float r, float g, float b)
{
	if (y >= 0 && x >= 0 && y <= rows_ && x < cols_)
	{
		int pos = (rows_ - y - 1) * (cols_ * 3) + (x * 3);
		if (pos + 2 < pixelCanvas_.size())
		{
			pixelCanvas_[pos] = r;
			pixelCanvas_[pos + 1] = g;
			pixelCanvas_[pos + 2] = b;
		}
	}
}

void PxCanvas::setPixel_unsafety(int x, int y, float r, float g, float b)
{
	int pos = (rows_ - y - 1) * (cols_ * 3) + (x * 3);
	pixelCanvas_[pos] = r;
	pixelCanvas_[pos + 1] = g;
	pixelCanvas_[pos + 2] = b;
}

void PxCanvas::setPixel(float r, float g, float b)
{
	setPixel(mousePosCol_, mousePosRow_, r, g, b);
}

void PxCanvas::setPixel(int x, int y, glm::vec3 color)
{
	setPixel(x, y, color.x, color.y, color.z);
}

void PxCanvas::drawLine(int x, int y, GLfloat r, GLfloat g, GLfloat b, int end_x, int end_y, int width)
{
	if (y >= 0 && x >= 0 && end_y >= 0 && end_x >= 0)
	{
		glm::vec2 move = glm::vec2(x - end_x, y - end_y);
		double len = glm::length(move);
		double stepX = move.x / len;
		double stepY = move.y / len;
		for (int brushi = -width / 2; brushi <= width / 2; ++brushi)
		{
			for (int brushj = -width / 2; brushj <= width / 2; ++brushj)
			{
				for (int k = 0; k < ceil(len); k++)
				{
					setPixel(end_x + static_cast<int>(stepX * k) + brushj, end_y + static_cast<int>(stepY * k) + brushi, r, g, b);
				}
			}
		}
	}
}

void PxCanvas::drawCircle(int x, int y, GLfloat r, GLfloat g, GLfloat b, int radius, bool fill)
{
	int line_x = 0;
	int x1 = 0;
	int y1 = radius;
	int delta = 1 - 2 * radius;
	int error = 0;
	while (y1 >= 0)
	{
		if (fill)
		{
			for (line_x = x - x1; line_x <= x + x1; ++line_x)
			{
				setPixel(line_x, y + y1, r, g, b);
			}
			for (line_x; line_x >= x - x1; --line_x)
			{
				setPixel(line_x, y - y1, r, g, b);
			}
		}
		else
		{
			setPixel(x + x1, y + y1, r, g, b);
			setPixel(x + x1, y - y1, r, g, b);
			setPixel(x - x1, y + y1, r, g, b);
			setPixel(x - x1, y - y1, r, g, b);
		}
		error = 2 * (delta + y1) - 1;
		if ((delta < 0) && (error <= 0))
		{
			delta += 2 * ++x1 + 1;
			continue;
		}
		if ((delta > 0) && (error > 0))
		{
			delta -= 2 * --y1 + 1;
			continue;
		}
		delta += 2 * (++x1 - --y1);
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