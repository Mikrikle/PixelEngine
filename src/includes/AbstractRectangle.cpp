#include "PixelEngine.h"
using namespace px;
using namespace engine;

void AbstractRectangle::setUnderTextureColor(glm::mat4x3 color)
{
	genVAO(color, size_.x, size_.y);
}

void AbstractRectangle::setUnderTextureColor(glm::mat2x3 color)
{
	genVAO(color, size_.x, size_.y);
}

void AbstractRectangle::setUnderTextureColor(glm::vec3 color)
{
	genVAO(color, size_.x, size_.y);
}

void AbstractRectangle::setUnderTextureColor(float r, float g, float b)
{
	genVAO(glm::vec3(r, g, b), size_.x, size_.y);
}

void AbstractRectangle::draw()
{
	transformMatrix_ = glm::mat4(1.0f);
	shader_->use();
	shader_->setFloat("TextureOpacity", 1.0f - textureOpacity_);
	transformMatrix_ = glm::translate(transformMatrix_, glm::vec3(nullPos_.x, nullPos_.y, 0.0f));
	transformMatrix_ = glm::scale(transformMatrix_, glm::vec3(scale_, scale_, 1.0));
	glUniformMatrix4fv(glGetUniformLocation(shader_->ID, "transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix_));
	drawVAO();
}

AbstractRectangle::AbstractRectangle(float width, float height, Shader* shader, float scale, float posX, float posY)
	: AbstractRectangle(width, height, shader)
{
	setScale(scale);
	setPos(posX, posY);
}

AbstractRectangle::AbstractRectangle(float width, float height, Shader* shader)
	: ComponentBase(width * 2, height * 2)
{
	shader_ = shader;
	genTexture();
	genVAO(glm::vec3(0.5f), size_.x, size_.y);
}

AbstractRectangle::AbstractRectangle(Shader* shader)
	: ComponentBase(1.0f * 2, 1.0f * 2)
{
	shader_ = shader;
	genTexture();
}

void AbstractRectangle::reInit(float width, float height)
{
	size_ = FloatCoord{ width, height };
	genVAO(glm::vec3(0.5f), size_.x, size_.y);
}