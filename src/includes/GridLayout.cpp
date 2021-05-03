#include "PixelEngine.h"
using namespace px;

bool GridLayout::checkIterator(std::vector<gObj>::iterator it, int value)
{
	for (int i = 0; i < value; i++)
	{
		if (it - i == objects_.begin())
			return false;
	}
	return true;
}

void GridLayout::init(int rows, int cols, std::initializer_list<gObj> objects, float width, float height, float scale, float posX, float posY)
{
	setPos(posX, posY);
	setScale(scale);
	rows_ = rows;
	cols_ = cols;
	calculateCellSize();

	objects_.resize(rows * cols);
	auto it = objects_.begin();
	std::vector<gObj> temp = objects;
	for (auto& temp_obj : temp)
	{
		for (int i = cols, k = 1; i < rows * cols; i *= 2, ++k)
		{
			if (checkIterator(it, i) && (*(it - cols)).row_span > k)
			{
				it++;
				break;
			}
		}
		*it = temp_obj;
		if (it + (*it).col_span != objects_.end())
			it += (*it).col_span;
	}

	reInitObjects();
}

GridLayout::GridLayout(int rows, int cols, std::initializer_list<gObj> objects, float width, float height, float scale, float posX, float posY) :
	ComponentBase(width * 2.0f, height * 2.0f)
{
	init(rows, cols, objects, width, height, scale, posX, posY);
}

GridLayout::GridLayout(int rows, int cols, std::initializer_list<gObj> objects) :
	ComponentBase(2.0f, 2.0f)
{
	init(rows, cols, objects);
}

GridLayout::GridLayout() : ComponentBase(2.0f, 2.0f)
{
	init(1, 1, {});
}

void GridLayout::draw()
{
	std::for_each(objects_.begin(), objects_.end(), [](gObj& obj) {if (obj.obj_ptr != nullptr)obj.obj_ptr->draw(); });
}

void GridLayout::update()
{
	std::for_each(objects_.begin(), objects_.end(), [](gObj& obj) {if (obj.obj_ptr != nullptr)obj.obj_ptr->update(); });
}

void GridLayout::reInit(float width, float height)
{
	size_ = FloatCoord{ width, height };
	calculateCellSize();
	reInitObjects();
}

void GridLayout::calculateCellSize()
{
	cell_height_ = fabs(getScaledSIZE().y / rows_);
	cell_width_ = fabs(getScaledSIZE().x / cols_);
}

void GridLayout::reInitObjects()
{
	std::for_each(objects_.begin(), objects_.end(), [this](gObj& obj) {if (obj.obj_ptr != nullptr)obj.obj_ptr->reInit(cell_width_ * obj.col_span, cell_height_ * obj.row_span); });
	arrangeObjects();
}

void GridLayout::arrangeObjects()
{
	auto it = objects_.begin();
	for (int i = 0; i < rows_; ++i)
	{
		for (int j = 0; j < cols_; ++j)
		{
			if (it != objects_.end())
			{
				if ((*it).obj_ptr != nullptr)
					setObjectPosition(*it, i, j);
				++it;
			}
		}
	}
}

void GridLayout::setObjectPosition(gObj& obj, int nrow, int ncol)
{
	obj.obj_ptr->setPos(this->getScaledPos().x + ncol * cell_width_, this->getScaledPos().y + nrow * cell_height_);
}

void GridLayout::setScale(float scale)
{
	ComponentBase::setScale(scale);
	calculateCellSize();
	reInitObjects();
}

void GridLayout::IncreaseScale(float value)
{
	ComponentBase::IncreaseScale(value);
	calculateCellSize();
	reInitObjects();
}

void GridLayout::setPos(float x, float y)
{
	ComponentBase::setPos(x, y);
	arrangeObjects();
}

void GridLayout::IncreasePos(float moveX, float moveY)
{
	ComponentBase::IncreasePos(moveX, moveY);
	arrangeObjects();
}