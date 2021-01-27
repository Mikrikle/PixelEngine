#include "../includes/PixelEngine.h"


PixelCanvasObj::PixelCanvasObj(glm::mat4x3 bgcolor, int ROWS, int COLS) : shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt")
{
	this->TextureOpacity = 0.5f;
	this->ROWS = ROWS;
	this->COLS = COLS;
	this->transform = glm::mat4(1.0f);
	genCanvas(bgcolor);
	genTexture();
}

PixelCanvasObj::~PixelCanvasObj()
{
	glDeleteVertexArrays(1, &this->VAO);
}

void PixelCanvasObj::setOpacity(float value)
{
	if (value >= 0.0 && value <= 1.0)
		this->TextureOpacity = value;
}

void PixelCanvasObj::draw(float* canvas)
{
	setPixelTexture(canvas);
	shader.use();
	shader.setFloat("TextureOpacity", this->TextureOpacity);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void PixelCanvasObj::genCanvas(glm::mat4x3 color)
{
	GLfloat vertices[] = {
		1.0f,  1.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,   color[1].x, color[1].y, color[1].z, 1.0f, 0.0f,
	   -1.0f, -1.0f, 0.0f,   color[2].x, color[2].y, color[2].z, 0.0f, 0.0f,
	   -1.0f,  1.0f, 0.0f,   color[3].x, color[3].y, color[3].z, 0.0f, 1.0f,
	};
	genBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
}

void PixelCanvasObj::genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI)
{
	GLuint VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(this->VAO);
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
	glBindVertexArray(0);
}

void PixelCanvasObj::genTexture()
{
	glGenTextures(1, &this->TEXTURE);
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void PixelCanvasObj::setPixelTexture(float* canvas)
{
	glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, canvas);
}
