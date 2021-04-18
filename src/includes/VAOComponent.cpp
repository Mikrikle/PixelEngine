#include "PixelEngine.h"
using namespace px;
using namespace engine;

void VAOComponent::setTextureOpacity(float opacity)
{
	if (opacity >= 0.0 && opacity <= 1.0)
		textureOpacity_ = opacity;
}

VAOComponent::VAOComponent()
{
	TEXTURE = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
	textureOpacity_ = 0.5f;
	shader_ = nullptr;
	indicesSize_ = 0;
	isInited_ = false;
}

VAOComponent::~VAOComponent()
{
	glDeleteTextures(1, &TEXTURE);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void VAOComponent::genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI)
{
	if (isInited_)
	{
		glBindVertexArray(VAO);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeV, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeI, indices, GL_STATIC_DRAW);
	// coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	isInited_ = true;
}

void VAOComponent::genTexture()
{
	glGenTextures(1, &TEXTURE);
	glBindTexture(GL_TEXTURE_2D, TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void VAOComponent::setTexture(float* pixels, int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_FLOAT, pixels);
}

void VAOComponent::setColorAsTexture(float r, float g, float b)
{
	float pixels[3]{ r ,g ,b };
	glBindTexture(GL_TEXTURE_2D, TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_FLOAT, pixels);
}

void VAOComponent::setColorAsTexture(glm::vec3 color)
{
	VAOComponent::setColorAsTexture(color.x, color.y, color.z);
}

void VAOComponent::setImgTexture(std::string path)
{
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, TEXTURE);
		if (path.find(".png") != std::string::npos)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		else if (path.find(".jpg") != std::string::npos || path.find(".jpeg") != std::string::npos)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR::VAO::Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}