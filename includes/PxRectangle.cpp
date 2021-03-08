#include "../includes/PixelEngine.h"
using namespace Px;

PxRectangle::PxRectangle(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init();
}

PxRectangle::PxRectangle(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	AbstractRectangle(WIDTH, HEIGHT, bgcolor, shader, scale, posX, posY)
{
	init();
}

void PxRectangle::init()
{
	genTexture();
}