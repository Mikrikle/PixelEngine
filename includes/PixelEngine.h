#include "../shaders/shader_s.h"

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"


class PxEngine
{
public:
	static bool MouseLeftClick;
	static bool MouseRightClick;
	static unsigned int WindowSizeX;
	static unsigned int WindowSizeY;
	unsigned int MousePosRow = 0;
	unsigned int MousePosCol = 0;
	const int ROWS;
	const int COLS;
	int SIZE;
private:
	float** pixelCanvases = nullptr;
	float* mixLayerCanvas = nullptr;
	int currentCanvas = 0;
	int layersNum = 1;

	void initCanvases()
	{
		pixelCanvases = new float* [layersNum];
		for (int i = 0; i < layersNum; i++)
		{
			pixelCanvases[i] = new float[SIZE];
			for (int elem = 0; elem < SIZE; elem++)
				pixelCanvases[i][elem] = 0.0f;
		}
		mixLayerCanvas = new float[SIZE];
		for (int elem = 0; elem < SIZE; elem++)
			mixLayerCanvas[elem] = 0.0f;
	}

	void deleteCanvases()
	{
		for (int i = 0; i < layersNum; i++)
			delete[] pixelCanvases[i];
		delete[] pixelCanvases;
	}
public:

	PxEngine(int rows, int cols, unsigned int WindowSizeX, unsigned int WindowSizeY)
		:ROWS(rows), COLS(cols)
	{
		this->WindowSizeX = WindowSizeX;
		this->WindowSizeY = WindowSizeY;
		this->MouseLeftClick = false;
		this->MouseRightClick = false;
		this->SIZE = COLS * ROWS * 3;
		initCanvases();
	}

	~PxEngine()
	{
		deleteCanvases();
		delete[] mixLayerCanvas;
	}

	void addLayer()
	{
		float** NewPixelCanvases = new float* [layersNum + 1];
		for (int i = 0; i < layersNum + 1; i++)
			NewPixelCanvases[i] = new float[SIZE];

		for (int i = 0; i < layersNum; i++)
			for (int elem = 0; elem < SIZE; elem++)
				NewPixelCanvases[i][elem] = pixelCanvases[i][elem];

		deleteCanvases();
		layersNum++;
		pixelCanvases = NewPixelCanvases;
	}

	int getCurrentLayer()
	{
		return currentCanvas;
	}

	void setLayer(int value)
	{
		if (value >= 0 && value < layersNum)
			currentCanvas = value;
	}

	float* getCanvas()
	{
		return pixelCanvases[currentCanvas];
	}

	float* getMixLayerCanvas()
	{
		for (int elem = 0; elem < SIZE; elem++)
			for (int i = 0; i < layersNum; i++)
				if (pixelCanvases[currentCanvas][elem] > mixLayerCanvas[elem])
					mixLayerCanvas[elem] = pixelCanvases[currentCanvas][elem];
		return mixLayerCanvas;
	}

	void setPixel(int i, int j, float r, float g, float b)
	{
		if (i * (COLS * 3) + j * 3 + 3 < SIZE && i * (COLS * 3) + j * 3 + 3 > 0)
		{
			i = ROWS - i - 1;
			pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3] = r;
			pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3 + 1] = g;
			pixelCanvases[currentCanvas][i * (COLS * 3) + j * 3 + 2] = b;
		}
	}

	void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width)
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
					setPixel(end_i + (stepi * k) + brushi, end_j + (stepj * k) + brushj, r, g, b);
				}
			}
		}
	}

	int TransformMouseXtoCol(unsigned int MousePosX)
	{
		return (float)(MousePosX % WindowSizeX) / ((float)WindowSizeX / COLS);
	}

	int TransformMouseYtoRow(unsigned int MousePosY)
	{
		return (float)(MousePosY % WindowSizeY) / ((float)WindowSizeY / ROWS);
	}
};

bool PxEngine::MouseLeftClick = false;
bool PxEngine::MouseRightClick = false;
unsigned int PxEngine::WindowSizeX = 1;
unsigned int PxEngine::WindowSizeY = 1;


class PixelDraw
{
private:
	float TextureOpacity;
	unsigned int VAO;
	unsigned int TEXTURE;
	int ROWS;
	int COLS;
	glm::mat4 transform = glm::mat4(1.0f);
public:
	Shader shader;

	PixelDraw(glm::mat4x3 bgcolor, int ROWS, int COLS) : shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt")
	{
		this->TextureOpacity = 0.5f;
		this->ROWS = ROWS;
		this->COLS = COLS;
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

	void draw(float* canvas)
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

	void setPixelTexture(float* canvas)
	{
		glBindTexture(GL_TEXTURE_2D, this->TEXTURE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLS, ROWS, 0, GL_RGB, GL_FLOAT, canvas);
	}
};