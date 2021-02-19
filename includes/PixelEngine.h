#pragma once
#include "../shaders/shader.h"

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

	/* creating and filling a 0.0 pixelCanvases and mixLayerCanvas */
	void initCanvases();

	/* delete all pixelCanvases */
	void deleteCanvases();

public:

	PxEngine(int rows, int cols, unsigned int WindowSizeX, unsigned int WindowSizeY);

	~PxEngine();

	/* returns number of rows (pixels per col) */
	int getROWS();

	/* returns number of cols (pixels per row) */
	int getCOLS();

	/* adding a new layer (array) to the end */
	void addLayer();

	/* 0 to delete the current layer, other values deletes the layer under the passed number */
	void deleteLayer(int delLvlNum);

	/* returns the number of the current layer (numbering starts with 1) */
	int getCurrentLayer();

	/* sets the rendering to the desired layer */
	void setLayer(int value);

	/* returns an array of pixels to be passed to the PixelCanvasObj */
	float* getCanvas();

	/* returns an array of pixels from all layers to be passed to the PixelCanvasObj
	* since there is no transparency, the pixel with the maximum RGB value will be displayed */
	float* getMixLayerCanvas();

	/* sets the desired color for the array element */
	void setPixel(int i, int j, float r, float g, float b);

	/* allows you to set a continuous line at 2 points */
	void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width);

	/* returns which column the mouse is in */
	int TransformMouseXtoCol(int MousePosX);

	/* returns which row the mouse is in */
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
	Shader shader;
public:
	

	PixelCanvasObj(glm::mat4x3 bgcolor, int ROWS, int COLS);

	~PixelCanvasObj();

	/* set the transparency of the texture, the higher, the more transparent, recomended value 0.2f */
	void setOpacity(float value);

	/* rendering this object */
	void draw(float* canvas);

	void setScale(float scale);

private:
	/* indexes for drawing a rectangular canvas from triangles*/
	GLuint indices[6] = {
		0, 1, 3,
		1, 2, 3
	};

	/* the creation of the vertices of the canvas */
	void genCanvas(glm::mat4x3 color);

	/* creating all the buffers necessary for OpenGL */
	void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI);

	/* configuring the texture buffer */
	void genTexture();

	/* sets an array of pixels as a texture */
	void setPixelTexture(float* canvas);

};