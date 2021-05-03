#pragma once

#include <vector>
#include <initializer_list>
#include <functional>
#include <algorithm>
#include <string>
#include <set>

#include "../shaders/shader.h"

#include "../../external/glm/glm/glm.hpp"
#include "../../external/glm/glm/gtc/matrix_transform.hpp"
#include "../../external/glm/glm/gtc/type_ptr.hpp"
#include "./img/stb_image.h"

#include "windowGLFM.h"

namespace px
{
	struct FloatCoord
	{
		float x;
		float y;
	};

	enum class Orientation
	{
		VERTICAL,
		HORIZONTAL
	};

	enum class RelativeBindingType
	{
		SIDE_TOP,
		SIDE_BOTTOM,
		SIDE_LEFT,
		SIDE_RIGHT
	};

	// global variables for event handling
	//   must be initialized to main.cpp
	extern Shader* DefaultShader;
	extern int windowWidth;
	extern int windowHeight;
	//   initialized in variables.cpp
	extern bool isMouseAlreadyUsed;
	extern bool isMouseLeftClick;
	extern bool isMouseRightClick;
	extern float absoluteMousePosX;
	extern float absoluteMousePosY;
	extern int mousePosX;
	extern int mousePosY;
	extern float mouseScrollX;
	extern float mouseScrollY;
	extern bool keyboardKeys[1024];
	extern float deltaTime;
	extern float lastFrameTime;

	// converting pixels to percentages, to set the width of object
	float transformPixToPctWidth(int pixel_size);
	// converting pixels to percentages, to set the height of object
	float transformPixToPctHeight(int pixel_size);

	namespace engine
	{
		// Class for working with openGL vertex array object
		class VAOComponent
		{
		public:
			// from 0 (fully transparent) to 1 (non-transparent)
			void setTextureOpacity(float opacity);
			void setColorAsTexture(float r, float g, float b);
			void setColorAsTexture(glm::vec3 color);
			void setTexture(float* pixels, int width, int height);
			void setImgTexture(std::string path);
		protected:
			bool isInited_ = false;
			float textureOpacity_ = 0.5f;
			unsigned int VAO = 0;
			unsigned int VBO = 0;
			unsigned int EBO = 0;
			unsigned int TEXTURE = 0;
			int indicesSize_ = 0;
			Shader* shader_ = nullptr;

			VAOComponent();
			~VAOComponent();
			virtual void drawVAO() = 0;
			void genBuffers(GLfloat* vertices, GLuint sizeV, GLuint* indices, GLuint sizeI);
			void genTexture();
		};

		// Class for creating a VAO rectangle from multiple triangles
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

			void genVAO(glm::mat4x3 color, float width, float height);
			void genVAO(glm::mat2x3 color, float width, float height);
			void genVAO(glm::vec3 color, float width, float height);
			void genVAO(float r, float g, float b, float width, float height);
			void drawVAO() override;
		};

		// something with size and potiiton.
		class ComponentBase
		{
		public:
			float getScale() const;
			void setPosAtCenterObj(ComponentBase& obj);
			void setPosAtCenter();
			void setPosRelativeTo(ComponentBase& obj, RelativeBindingType side, float offsetX, float offsetY);
			void setPosAtAbsoluteGrid(int row_num, int col_num);
			FloatCoord getCenterPos() const;
			FloatCoord getPos() const;
			FloatCoord getScaledSIZE() const;
			FloatCoord getSIZE() const;
			bool isMouseOn() const;
			bool isClickOn() const;
			virtual void IncreaseScale(float value);
			virtual void setScale(float scale);
			virtual void setPos(float x, float y);
			virtual void IncreasePos(float moveX, float moveY);
			virtual void draw() {};
			virtual void update() {};
			virtual void reInit(float width, float height) {};
		protected:
			float scale_ = 1.0f;
			FloatCoord size_;
			FloatCoord nullPos_;
			glm::mat4 transformMatrix_;

			void normilizeNullCoords();
			ComponentBase(float width, float height);
		};

		// Сlass that binds the VAOrectangle to the position on the screen and events
		class AbstractRectangle : public VAOrectangle, public ComponentBase
		{
		public:
			// setting the background color that will blend with the texture, if texture opacity < 1
			void setUnderTextureColor(glm::mat4x3 color);
			void setUnderTextureColor(glm::mat2x3 color);
			void setUnderTextureColor(glm::vec3 color);
			void setUnderTextureColor(float r, float g, float b);
			void reInit(float width, float height) override;
			void draw() override;
		protected:
			AbstractRectangle(float width, float height, Shader* shader, float scale, float posX, float posY);
			AbstractRectangle(float width, float height, Shader* shader);
			AbstractRectangle(Shader* shader);
		};

		// class for basic functions for processing mouse clicks on widgets
		class ComponentClickableWidget
		{
		public:
			// set the transparency of the texture when the mouse is not pressed on the object
			void setNormalOpacity(float opacity);
			// set the transparency of the texture when the mouse is pressed on the object
			void setActiveOpacity(float opacity);
			// set the transparency of the texture when the mouse is positioned on the object
			void setMouseOnOpacity(float opacity);
			// quickly set all new opacity values
			void setAllOpacityes(float normalOpacity, float activeOpacity, float mouseOnOpacity);
		protected:
			ComponentClickableWidget();
			float normalOpacity_ = 1.0f;
			float activeOpacity_ = 0.0f;
			float mouseOnOpacity_ = 0.5f;
			bool isPressed_ = false;
		};
	}

	// ============================grid============================

	// {object = nullptr, row_span = 1, col_span = 1}
	struct gObj
	{
		engine::ComponentBase* obj_ptr{ nullptr };
		int row_span{ 1 };
		int col_span{ 1 };
	};

	class GridLayout : public engine::ComponentBase
	{
	public:
		GridLayout(int rows, int cols, std::initializer_list<gObj> objects, float width, float height, float scale, float posX, float posY);
		GridLayout(int rows, int cols, std::initializer_list<gObj> objects);
		GridLayout();
		void init(int rows, int cols, std::initializer_list<gObj> objects,
			float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f);
		void draw() override;
		void update() override;
		void reInit(float width, float height) override;
		void setScale(float scale) override;
		void IncreaseScale(float value) override;
		void setPos(float x, float y) override;
		void IncreasePos(float moveX, float moveY) override;
	private:
		std::vector<gObj> objects_;
		int rows_;
		int cols_;
		void calculateCellSize();
		float cell_height_;
		float cell_width_;
		void arrangeObjects();
		void reInitObjects();
		void setObjectPosition(gObj& obj, int nrow, int ncol);
		bool checkIterator(std::vector<gObj>::iterator it, int value);
	};

	// ============================managers============================

	// Class for rendering and processing events for a group of objects
	class ManagerObjects
	{
	public:
		ManagerObjects();
		ManagerObjects(std::vector<engine::ComponentBase*> objects);
		ManagerObjects(std::initializer_list<engine::ComponentBase*> objects);
		void init(std::initializer_list<engine::ComponentBase*> objects);
		void appendObj(engine::ComponentBase* obj);
		void drawAll();
		void updateAll();
		void addToIgnoreDrawingLsist(int index);
		void addToIgnoreUpdatingLsist(int index);
		void removeFromIgnoreDrawingList(int index);
		void removeFromIgnoreUpdatingList(int index);
	private:
		std::vector<engine::ComponentBase*> objects_;
		std::set<int> ignoreDrawList_;
		bool isInDrawIgnore(int index);
		std::set<int> ignoreUpdateList_;
		bool isInUpdateIgnore(int index);
	};

	// Class for placing objects relative to each other
	class ManagerPercentagesPosition
	{
	public:
		static void placeHorizontally(std::vector<engine::ComponentBase*> objects, float offset);
		static void placeVertically(std::vector<engine::ComponentBase*> objects, float offset);
	private:
		ManagerPercentagesPosition();
	};

	// ============================objects============================

	// Simple object with no additional functions
	class PxRectangle : public engine::AbstractRectangle
	{
	public:
		PxRectangle(float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
	};

	// Canvas based on a pixel texture of the selected size
	class PxCanvas : public engine::AbstractRectangle
	{
	public:
		PxCanvas(int rows, int cols, float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
		~PxCanvas();
		int transformPercentsToCoordX(float absolute_x) const;
		int transformPercentsToCoordY(float absolute_y) const;
		glm::vec3 getPixel() const;
		glm::vec3 getPixel(int row, int col) const;
		void setPixel(int x, int y, float r, float g, float b);
		void setPixel(float r, float g, float b);
		void setPixel(int x, int y, glm::vec3 color);
		void setPixel_unsafety(int i, int j, float r, float g, float b);
		void drawLine(int x, int y, GLfloat r, GLfloat g, GLfloat b, int end_x, int end_y, int width);
		void drawCircle(int x, int y, GLfloat r, GLfloat g, GLfloat b, int radius, bool fill = true);
		void fillBlack();
		void fillWhite();
		void draw() override;
		void update() override;
		int getRows() const;
		int getCols() const;
		int getMouseCol() const;
		int getMouseRow() const;

	private:
		int rows_;
		int cols_;
		std::vector<float> pixelCanvas_;
		int mousePosCol_ = 0;
		int mousePosRow_ = 0;
	};

	// full-screen object with no additional functions
	class PxBackground : public engine::AbstractRectangle
	{
	public:
		PxBackground(Shader* shader = DefaultShader);
	};

	// ============================widgets============================

	// the button that the passed function is called when clicked
	class PxButton : public engine::AbstractRectangle, public engine::ComponentClickableWidget
	{
	public:
		PxButton(std::function<void(PxButton* self)> callback = nullptr,
			float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
		void update() override;

	private:
		std::function<void(PxButton* self)> callback_;
	};

	// stores the true or false state
	class PxSwitch : public engine::AbstractRectangle, public engine::ComponentClickableWidget
	{
	public:
		PxSwitch(std::function<void(PxSwitch* self)> callback = nullptr, Orientation orientation = px::Orientation::HORIZONTAL,
			float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
		void update() override;
		void draw();
		PxRectangle toggle;

		bool isActive() const;
		void setScale(float scale) override;
		void IncreaseScale(float value) override;
		void setPos(float x, float y) override;
		void IncreasePos(float moveX, float moveY) override;
		void reInit(float width, float height) override;
	private:
		std::function<void(PxSwitch* self)> callback_;
		bool active_ = false;
		Orientation orientation_;
		void setTogglePos();
	};

	// return float percentages (0 - 100) or int step (by default, the number of steps is 100)
	class PxSlider : public engine::AbstractRectangle, public engine::ComponentClickableWidget
	{
	public:

		PxSlider(std::function<void(PxSlider* self)> callback = nullptr, Orientation orientation = px::Orientation::HORIZONTAL,
			float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
		void update() override;
		void draw();
		PxRectangle toggle;
		PxRectangle toggle_route_line;

		void setStep(int step);
		float getPercentages() const;
		int getValue() const;
		void setScale(float scale) override;
		void IncreaseScale(float value) override;
		void setPos(float x, float y) override;
		void IncreasePos(float moveX, float moveY) override;
		void reInit(float width, float height) override;
	private:
		std::function<void(PxSlider* self)> callback_;
		float percentages_ = 50.0f;
		float stepSize_ = 1;
		bool mouseGrab_ = false;
		Orientation orientation_;
		void setPercentages();
	};

	// stores the true or false state
	class PxCheckBox : public engine::AbstractRectangle, public engine::ComponentClickableWidget
	{
	public:
		PxCheckBox(std::function<void(PxCheckBox* self)> callback = nullptr,
			float width = 1.0f, float height = 1.0f, float scale = 1.0f, float posX = -1.0f, float posY = -1.0f, Shader* shader = DefaultShader);
		void update() override;
		void draw();
		PxRectangle mark;

		bool isActive() const;
		void setScale(float scale) override;
		void IncreaseScale(float value) override;
		void setPos(float x, float y) override;
		void IncreasePos(float moveX, float moveY) override;
		void reInit(float width, float height) override;
	private:
		std::function<void(PxCheckBox* self)> callback_;
		bool active_ = false;
	};

	// ============================App============================

	class PxBaseApp
	{
	public:
		virtual void objectsSetting() {};
		virtual void objectsEvents() {};

		void update()
		{
			manager.updateAll();
			objectsEvents();
		}
		void draw()
		{
			manager.drawAll();
		}
	protected:
		void init()
		{
			objectsSetting();
		}

		px::GridLayout grid;
		px::ManagerObjects manager;
	};
}