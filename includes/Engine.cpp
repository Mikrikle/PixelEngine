#include "../shaders/shader_s.h"

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"


const int ROWS = 800;
const int COLS = 800;
unsigned int WindowSizeX = 800;
unsigned int WindowSizeY = 800;
unsigned int MousePosRow = 0;
unsigned int MousePosCol = 0;
bool MouseLeftClick = false;
bool MouseRightClick = false;


float pixelCanvas[ROWS * COLS * 3]{};


void setPixel(float* canvas, int i, int j, float r, float g, float b)
{
	if (i * (COLS * 3) + j * 3 + 2 < ROWS * COLS * 3 && i * (COLS * 3) + j * 3 + 2 > 0)
	{
		i = ROWS - i - 1;
		canvas[i * (COLS * 3) + j * 3] = r;
		canvas[i * (COLS * 3) + j * 3 + 1] = g;
		canvas[i * (COLS * 3) + j * 3 + 2] = b;
	}
}

void setLine(GLfloat* pixels, int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
{
	glm::vec2 move = glm::vec2(i - end_i, j - end_j);
	double len = glm::length(move);
	double stepi = move.x / len;
	double stepj = move.y / len;
	for (int brushi = -width / 2; brushi <= width / 2; brushi++)
	{
		for (int brushj = -width / 2; brushj <= width / 2; brushj++)
		{
			for (int k = 0; k < (int)ceil(len); k++)
			{
				setPixel(pixels, end_i + (stepi * k) + brushi, end_j + (stepj * k) + brushj, r, g, b);
			}
		}
	}
}

void setAllPixels(float* canvas, int arr[ROWS][COLS], float r, float g, float b)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			setPixel(canvas, i, j, r, g, b);
		}
	}
}

static int TransformMouseXtoCol(unsigned int MousePosX)
{
	return (float)(MousePosX % WindowSizeX) / ((float)WindowSizeX / COLS);
}

static int TransformMouseYtoRow(unsigned int MousePosY)
{
	return (float)(MousePosY % WindowSizeY) / ((float)WindowSizeY / ROWS);
}


class PixelDraw
{
private:
	float TextureOpacity;
	unsigned int VAO;
	unsigned int TEXTURE;
	glm::mat4 transform = glm::mat4(1.0f);
public:
	Shader shader;

	unsigned int getWindowWidth()
	{
		return WindowSizeX;
	}

	unsigned int getWindowHeight()
	{
		return WindowSizeY;
	}

	PixelDraw(glm::mat4x3 bgcolor) : shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt")
	{
		this->TextureOpacity = 0.5f;
		genCanvas(bgcolor);
		genTexture();
	}

	~PixelDraw()
	{
		glDeleteVertexArrays(1, &this->VAO);
	}

	void setOpacity(float value)
	{
		if (value >= 0.0 && value <= 1.0)
			this->TextureOpacity = value;
	}

	void draw(float *canvas)
	{
		setPixelTexture(canvas);
		shader.use();
		shader.setFloat("TextureOpacity", this->TextureOpacity);
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
		glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
	}
private:
	GLuint indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	void genCanvas(glm::mat4x3 color)
	{
		GLfloat vertices[] = {
			1.0f,  1.0f, 0.0f,   color[0].x, color[0].y, color[0].z, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f,   color[1].x, color[1].y, color[1].z, 1.0f, 0.0f,
		   -1.0f, -1.0f, 0.0f,   color[2].x, color[2].y, color[2].z, 0.0f, 0.0f,
		   -1.0f,  1.0f, 0.0f,   color[3].x, color[3].y, color[3].z, 0.0f, 1.0f,
		};
		genBuffers(vertices, sizeof(vertices), indices, sizeof(indices));
	}

	void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI)
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

	void genTexture()
	{
		glGenTextures(1, &this->TEXTURE);
		glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void setPixelTexture(float *canvas)
	{
		glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, canvas);
	}
};