#include "PixelEngine.h"
using namespace Px;


PxBackground::PxBackground(glm::mat4x3 bgcolor, Shader* shader) :
	AbstractRectangle(2.0f, 2.0f, bgcolor, shader, 1.0f, 1.0f, 1.0f)
{
}


PxBackground::PxBackground(glm::mat2x3 bgcolor, Shader* shader) :
	AbstractRectangle(2.0f, 2.0f, bgcolor, shader, 1.0f, 1.0f, 1.0f)
{
}