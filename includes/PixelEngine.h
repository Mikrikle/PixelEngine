#pragma once
#include "../shaders/shader.h"

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

typedef struct
{
	float x;
	float y;
} PxCoord;


class Px
{
public:
	static int WindowSizeX;
	static int WindowSizeY;
	static bool MouseLeftClick;
	static bool MouseRightClick;
protected:
	Px() {};
};

/* each object must have a width and a height */
class PxBaseObj : public Px
{
public:
	float WIDTH;
	float HEIGHT;

	float getWIDTH();

	float getHEIGHT();

protected:
	PxBaseObj(float WIDTH, float HEIGHT);
};

/* class for working with the position of the object on the window */
class PxMovableObj : public PxBaseObj
{
protected:
	float scale;
	PxCoord translatePos;
	PxCoord nullPos;
	PxCoord absoluteMousePos;
	PxCoord realPos;

public:
	/* truncates the position value to 2 decimal places */
	void normilizeNullCoords();

	/* sets the zoom level of the object */
	void setScale(float scale);

	float getScale();

	/* add a value to the current scale */
	void increaseScale(float value);

	/* sets the position of the object relative to its middle */
	void setTranslate(float x, float y);

	/* add a value to the current position */
	void increaseTranslate(float moveX, float moveY);

	/* get the position of the lower left corner */
	PxCoord getNullPos();

	bool isClickOn(int x, int y);

protected:
	PxMovableObj(float WIDTH, float HEIGHT);
};

/* object with a pixel-changing texture and a gradient background */
class PxCanvasObj : public PxMovableObj
{
private:
	float TextureOpacity;
	unsigned int VAO;
	unsigned int TEXTURE;
	glm::mat4 transform;
	Shader* shader;
	int ROWS;
	int COLS;
	int SIZE;
	float* pixelCanvas;

protected:
	PxCanvasObj(int ROWS, int COLS, float WIDTH, float HEIGHT);

	~PxCanvasObj();

	/* rendering this object */
	void render();

	/* returns number of rows (pixels per col) */
	int getROWS();

	/* returns number of cols (pixels per row) */
	int getCOLS();
public:

	/* setting the background and shader for drawing an object. full window size */
	void initCanvas(glm::mat4x3 bgcolor, Shader* shader);

	/* setting the background and shader for drawing an object also scale and position */
	void initCanvas(glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY);

	/* changes the background, with 3 values (R G B) for each of the 4 points. Starting from the top left point by clockwise direction */
	void changeBackground(glm::mat4x3 color);

	/* set the transparency of the texture, the higher, the more transparent, recomended value 0.2f */
	void setOpacity(float value);

	/* sets the desired color for the array element */
	void setPixel(int i, int j, float r, float g, float b);

	/* allows you to set a continuous line at 2 points */
	void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width);

	/* set all pixels to 0.0f */
	void clear();

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
	void setPixelTexture();
};


/* the main class consisting of an array of pixels and a canvas for displaying them */
class PixelCanvas : public PxCanvasObj
{
public:
	int MousePosCol;
	int MousePosRow;

	PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, int WindowSizeX, int WindowSizeY);

	PixelCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT);

	void draw();

	/* changes the values of variables MousePosCol and MousePosRow to the corresponding values*/
	void TransformMousePosToGrid(int x, int y);
};