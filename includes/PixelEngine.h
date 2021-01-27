#pragma once
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
	unsigned int MousePosRow;
	unsigned int MousePosCol;
private:
	int ROWS;
	int COLS;
	int SIZE;
	float** pixelCanvases;
	float* mixLayerCanvas;
	int currentCanvas;
	int layersNum;

	void initCanvases();

	void deleteCanvases();

public:

	PxEngine(int rows, int cols, unsigned int WindowSizeX, unsigned int WindowSizeY);

	~PxEngine();

	int getROWS();

	int getCOLS();

	void addLayer();

	int getCurrentLayer();

	void setLayer(int value);

	float* getCanvas();

	float* getMixLayerCanvas();

	void setPixel(int i, int j, float r, float g, float b);

	void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width);

	int TransformMouseXtoCol(int MousePosX);

	int TransformMouseYtoRow(int MousePosY);

};


class PixelCanvasObj
{
private:
	float TextureOpacity;
	unsigned int VAO;
	unsigned int TEXTURE;
	int ROWS;
	int COLS;
	glm::mat4 transform;
public:
	Shader shader;

	PixelCanvasObj(glm::mat4x3 bgcolor, int ROWS, int COLS);

	~PixelCanvasObj();

	void setOpacity(float value);

	void draw(float* canvas);

private:
	GLuint indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	void genCanvas(glm::mat4x3 color);

	void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI);

	void genTexture();

	void setPixelTexture(float* canvas);

};