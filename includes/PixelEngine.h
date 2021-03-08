#pragma once
#include "../shaders/shader.h"

#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

namespace Px
{
	class ComponentBase;

	typedef struct
	{
		float x;
		float y;
	} FloatCoord;

	extern bool MouseLeftClick;
	extern bool MouseRightClick;
	extern float absoluteMousePosX;
	extern float absoluteMousePosY;
	extern int WindowSizeX;
	extern int WindowSizeY;
	extern int MousePosX;
	extern int MousePosY;
	extern float ScrollX;
	extern float ScrollY;
	extern bool Keys[1024];
	extern float deltaTime;
	extern float lastFrame;

	class ObjectManager
	{
	public:
		ComponentBase** objects;
		int objectsCounter;

		ObjectManager();
		~ObjectManager();
		void drawAll();
		void updateAll();
		void appendObj(ComponentBase& obj);
		void appendObjects(int n, ComponentBase* objects[]);
	};

	class VAOComponent
	{
	public:
		void setOpacity(float value);
		void setBaseColor(float r, float g, float b);
	protected:
		float TextureOpacity;
		unsigned int VAO;
		unsigned int TEXTURE;
		int indicesSize;
		Shader* shader;

		VAOComponent();
		~VAOComponent();
		virtual void drawVAO() = 0;
		void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI, bool useTexture);
		void genTexture();
		void setTexture(float* pixels, int ROWS, int COLS);
	};

	class VAOrectangle : public VAOComponent
	{
	protected:
		GLuint indices2triangles[6] = {
			0, 1, 3,
			1, 2, 3
		};

		GLuint indices4triangles[12] = {
			0, 4, 3,
			0, 4, 1,
			3, 4, 2,
			1, 4, 2,
		};

		void genVAO(glm::mat4x3 color, float WIDTH, float HEIGHT, int indicesSize);
		void genVAO(glm::mat2x3 color, float WIDTH, float HEIGHT, int indicesSize);
		void drawVAO() override;
	};

	class VAOregularPolygon : public VAOComponent
	{
	protected:
		GLuint* indices = nullptr;
		GLuint verticesNumber;

		~VAOregularPolygon();
		void genVAO(glm::mat2x3 color, float radius, int vertices_count);
		void drawVAO() override;
	};

	class ComponentBase 
	{
	public:
		void setScale(float scale);
		float getScale();
		void changeScale(float value);
		void setPos(float x, float y);
		void changePos(float moveX, float moveY);
		FloatCoord getScaledPos();
		FloatCoord getPos();
		FloatCoord getScaledSIZE();
		FloatCoord getSIZE();
		bool isMouseOn();
		bool isClickOn();
		bool ComponentBase::isRectCollisionWith(ComponentBase& obj);
		bool ComponentBase::isRoundCollisionWith(ComponentBase& obj);
		virtual void draw() {};
		virtual void update() {};

	protected:
		float scale;
		FloatCoord SIZE;
		FloatCoord translatePos;
		FloatCoord nullPos;
		FloatCoord realPos;
		glm::mat4 transform;

		void normilizeNullCoords();
		void updateRealPos();
		ComponentBase(float WIDTH, float HEIGHT);
	};

	class AbstractRectangle : public VAOrectangle, public ComponentBase
	{
	public:
		void changeBackground(glm::mat4x3 color);
		void changeBackground(glm::mat2x3 color);
		void draw() override;
	protected:
		AbstractRectangle(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		AbstractRectangle(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY);

	private:
		AbstractRectangle(float WIDTH, float HEIGHT, Shader* shader, float scale, float posX, float posY);
	};


	class PxRectangle : public AbstractRectangle
	{
	public:
		PxRectangle(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		PxRectangle(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY);
	private:
		void init();
	};


	class PxCanvas : public AbstractRectangle
	{
	public:
		PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		PxCanvas(int ROWS, int COLS, float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		~PxCanvas();
		void setPixel(int i, int j, float r, float g, float b);
		void setPixel(float r, float g, float b);
		void setLine(int i, int j, GLfloat r, GLfloat g, GLfloat b, int end_i, int end_j, int width);
		void clear();
		void draw() override;
		void update() override;
		int getROWS();
		int getCOLS();
		int getMouseCol();
		int getMouseRow();

	private:
		int ROWS;
		int COLS;
		int SIZE;
		float* pixelCanvas;
		int MousePosCol;
		int MousePosRow;

		void init(int ROWS, int COLS);
	};


	class PxBackground : public AbstractRectangle
	{
	public:
		PxBackground(glm::mat4x3 color, Shader* shader);
		PxBackground(glm::mat2x3 color, Shader* shader);
	};


	class PxButton : public AbstractRectangle
	{
	public:
		PxButton(float WIDTH, float HEIGHT, glm::mat4x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(PxButton* self));
		PxButton(float WIDTH, float HEIGHT, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY, void (*btncallback)(PxButton* self));
		void update() override;

	private:
		void init(void (*btncallback)(PxButton* self));
		void (*btncallback)(PxButton* self);
	};


	class AbstractRegularPolygon : public VAOregularPolygon, public ComponentBase
	{
	protected:
		AbstractRegularPolygon(float radius, float vertices_count, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY);
		void changeBackground(glm::mat2x3 color);
		void draw() override;
	private:
		int vertices_count;
	};


	class PxRegularPolygon : public AbstractRegularPolygon
	{
	public:
		PxRegularPolygon(float radius, float vertices_count, glm::mat2x3 bgcolor, Shader* shader, float scale, float posX, float posY);
	};
}