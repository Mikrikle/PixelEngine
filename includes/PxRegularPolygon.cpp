#include "../includes/PixelEngine.h"
using namespace Px;

PxRegularPolygon::PxRegularPolygon(float radius, float vertices_count, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY) :
	AbstractRegularPolygon(radius, vertices_count, bgcolor, shader, scale, posX, posY)
{
}
