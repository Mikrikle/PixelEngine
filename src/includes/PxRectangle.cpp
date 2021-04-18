#include "PixelEngine.h"
using namespace px;

PxRectangle::PxRectangle(float width, float height, float scale, float posX, float posY, Shader* shader) :
	AbstractRectangle(width, height, shader)
{
	setScale(scale);
	setPos(posX, posY);
	genTexture();
}