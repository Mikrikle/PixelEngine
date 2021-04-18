#include "PixelEngine.h"
using namespace px;

PxBackground::PxBackground(Shader* shader) :
	AbstractRectangle(1.0f, 1.0f, shader, 1.0f, -1.0f, -1.0f)
{
}