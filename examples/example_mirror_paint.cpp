#include <iostream>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"


void drawMirrored(px::PxCanvas& self, int lasti, int lastj, GLfloat r, GLfloat g, GLfloat b, int brushsize, int axes, bool symmetry);

int px::windowWidth = 800;
int px::windowHeight = px::windowWidth;
const int ROWS = px::windowWidth;
const int COLS = px::windowWidth;

Window window(px::windowWidth, px::windowHeight, "Paint");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

px::PxCanvas px_canvas(ROWS, COLS);

px::ManagerObjects manager{ &px_canvas};

int lasti = 0;
int lastj = 0;
int brushsize = 2;
int axes = 8;
bool symmetry = true;
glm::vec3 color(1.0f, 0.0f, 0.0f);

void objectsEvents()
{
	if (px::isMouseLeftClick)
		drawMirrored(px_canvas, lasti, lastj, color.x, color.y, color.z, brushsize, axes, symmetry);
	if (px::isMouseRightClick)
		drawMirrored(px_canvas, lasti, lastj, 0.0f, 0.0f, 0.0f, brushsize, axes, symmetry);

	if ((axes > 1 && px::mouseScrollY < 0) || (axes < 100 && px::mouseScrollY > 0))
	{
		axes += (px::mouseScrollY > 0) ? 1 : -1;
		std::cout << "axes: " << axes << std::endl;
	}
	if (px::keyboardKeys[GLFW_KEY_1])
		color = glm::vec3(1.0f, 0.0f, 0.0f);
	if (px::keyboardKeys[GLFW_KEY_2])
		color = glm::vec3(0.0f, 1.0f, 0.0f);
	if (px::keyboardKeys[GLFW_KEY_3])
		color = glm::vec3(0.0f, 0.0f, 1.0f);
	px::mouseScrollY = 0;
}

void btn_clear_px(px::PxButton* btn)
{
	px_canvas.fillBlack();
}

int main()
{
	px_canvas.setUnderTextureColor(glm::vec3(0.05f, 0.05f, 0.05f));

	while (!window.isShouldClose())
	{
		window.clearWindow(0.5f, 0.5f, 0.5f);
		manager.drawAll();
		manager.updateAll();
		objectsEvents();

		lasti = px_canvas.getMouseRow();
		lastj = px_canvas.getMouseCol();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}

void setPolarCoords(float x, float y, float* radius, float* f)
{
	glm::vec2 Pos = glm::vec2(x - COLS / 2, y - ROWS / 2);
	*radius = glm::length(Pos);
	*f = atan(Pos.y / Pos.x);
	if (Pos.x < 0)
		*f += + 3.14159265;
}

void drawMirrored(px::PxCanvas& self, int lasti, int lastj, GLfloat r, GLfloat g, GLfloat b, int brushsize, int axes, bool symmetry)
{
	double angle = glm::radians(360.0 / axes);
	float new_r=0, new_f=0;
	setPolarCoords(self.getMouseCol(), self.getMouseRow(), &new_r, &new_f);
	float old_r=0, old_f=0;
	setPolarCoords(lastj, lasti, &old_r, &old_f);

	for (int axe = 0; axe < axes; axe++)
	{
		if (new_r < ROWS / 2)
		{
			self.setLine(ROWS / 2 + sin(new_f + (angle * axe)) * new_r, COLS / 2 + cos(new_f + (angle * axe)) * new_r,
				r,g, b,
				ROWS / 2 + sin(old_f + (angle * axe)) * old_r, COLS / 2 + cos(old_f + (angle * axe)) * old_r,
				brushsize
			);
			if (symmetry)
			{
				self.setLine(ROWS / 2 + cos(new_f + (angle * axe + angle)) * new_r, COLS / 2 + sin(new_f + (angle * axe + angle)) * new_r,
					r, g, b,
					ROWS / 2 + cos(old_f + (angle * axe + angle)) * old_r, COLS / 2 + sin(old_f + (angle * axe + angle)) * old_r,
					brushsize
				);
			}
		}
	}
}