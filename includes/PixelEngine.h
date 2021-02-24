#pragma once
#include "../shaders/shader.h"

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

namespace Px
{
	enum MovingType{STATIC, MOVABLE, SCALED, FULL};

	typedef struct
	{
		float x;
		float y;
	} FloatCoord;

	extern bool MouseLeftClick;
	extern bool MouseRightClick;
	extern int WindowSizeX;
	extern int WindowSizeY;
	extern int MousePosX;
	extern int MousePosY;
	extern float ScrollX;
	extern float ScrollY;
	extern bool Keys[1024];

	class ComponentEvents
	{
	public:
		float moveSpeed;
		int baseMoveMod;

		void setMoveSpeed(float value);
		void setMovable(int value);
		virtual void eventProcessing(float deltaTime) {};

	protected:
		ComponentEvents();
	};

	class EventsDefaultManager
	{
	public:
		ComponentEvents** objects;
		int objectsCounter;

		EventsDefaultManager();
		~EventsDefaultManager();
		void updateEvents(float deltaTime);
		void appendObj(ComponentEvents& obj);
	};

	class VAOrectangle
	{
	public:
		void setOpacity(float value);

	protected:
		float TextureOpacity;
		unsigned int VAO;
		unsigned int TEXTURE;
		Shader* shader;
		GLuint indices[6] = {
			0, 1, 3,
			1, 2, 3
		};

		VAOrectangle();
		~VAOrectangle();
		void genBackground(glm::mat4x3 color, float WIDTH, float HEIGHT);
		void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI);
		void genTexture();
		void drawVAO();
	};


	class ComponentBase
	{
	public:
		float getWIDTH();
		float getHEIGHT();

	protected:
		float WIDTH;
		float HEIGHT;

		ComponentBase(float WIDTH, float HEIGHT);
		ComponentBase();
	};


	class ComponentMovable : public ComponentBase
	{
	public:
		void setScale(float scale);
		float getScale();
		void increaseScale(float value);
		void setTranslate(float x, float y);
		void increaseTranslate(float moveX, float moveY);
		FloatCoord getNullPos();
		bool isClickOn(int x, int y);

	protected:
		float scale;
		FloatCoord translatePos;
		FloatCoord nullPos;
		FloatCoord absoluteMousePos;
		FloatCoord realPos;
		glm::mat4 transform;

		ComponentMovable(float WIDTH, float HEIGHT);
		void normilizeNullCoords();
	};


	class PxCanvas : public ComponentMovable, public VAOrectangle, public ComponentEvents
	{
	public:
		PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader);
		PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		~PxCanvas();
		void changeBackground(glm::mat4x3 color);
		void setPixel(int i, int j, float r, float g, float b);
		void setPixel(float r, float g, float b);
		void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width);
		void clear();
		void draw();
		void eventProcessing(float deltaTime) override;
		int getROWS();
		int getCOLS();

	private:
		int ROWS;
		int COLS;
		int SIZE;
		float* pixelCanvas;
		int MousePosCol;
		int MousePosRow;

		void setPixelTexture();
	};


	class PxStaticBackground : public ComponentBase, public VAOrectangle
	{
	public:
		PxStaticBackground(glm::mat4x3 color, Shader* shader);
		void changeBackground(glm::mat4x3 color);
		void draw();
	};


	class PxButton : public ComponentMovable, public VAOrectangle, public ComponentEvents
	{
	public:
		PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(ComponentMovable& obj), ComponentMovable& obj);
		void changeBackground(glm::mat4x3 color);
		void draw();
		void eventProcessing(float deltaTime) override;

	private:
		void (*btncallback)(ComponentMovable& obj);
		ComponentMovable* bindObj;
	};

}