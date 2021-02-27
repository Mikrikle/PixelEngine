/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"
#include "../includes/PxWindowEvents.h"

void drawMirrored(Px::PxCanvas& self, int lasti, int lastj, GLfloat r, GLfloat g, GLfloat b, int brushsize, int axes, bool symmetry);

const int ROWS = 800;
const int COLS = 800;
Px::EventsDefaultManager pxmanager;
Px::DrawManager drawmanager;


int lasti = 0;
int lastj = 0;
int brushsize = 2;
int axes = 5;
bool symmetry = true;

void event_px_on_click(Px::PxCanvas& self)
{
	if (Px::MouseLeftClick)
		drawMirrored(self, lasti, lastj, 0.0f, 1.0f, 0.0f, brushsize, axes, symmetry);
	if (Px::MouseRightClick)
		drawMirrored(self, lasti, lastj, 0.0f, 0.0f, 0.0f, brushsize, axes, symmetry);
}

void event_px_scroll(Px::PxCanvas& self)
{
	if ((axes > 1 && Px::ScrollY < 0) || (axes <= 50 && Px::ScrollY > 0))
	{
		axes += (Px::ScrollY > 0) ? 1 : -1;
		std::cout << "axes: " << axes << std::endl;
	}

	Px::ScrollY = 0;
}

void btn_clear_px(Px::PxCanvas& self)
{
	self.clear();
}

int main()
{
	Px::WindowSizeX = 1000;
	Px::WindowSizeY = 800;
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Paint");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");

	float colors[6]{ 2.0f, 2.0f, 2.0f, 1.0f, 1.0f, 1.0f };
	Px::PxCanvas px(ROWS, COLS, 0.8f, 1.0f, glm::make_mat2x3(colors), &shader, 1.0f, -0.2f, 0.0f, event_px_on_click, event_px_scroll, nullptr);
	px.setMoveSpeed(3.0f);
	px.setOpacity(0.2f);

	float btn_clear_colors[6]{ 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };
	Px::PxButtonForObj<Px::PxCanvas> btn_clear(0.2f, 0.1f, glm::make_mat2x3(btn_clear_colors), &shader, 1.0f, 0.8f, 0.9f, btn_clear_px, px);

	Px::ComponentEvents* events_objects[]{ &px, &btn_clear };
	pxmanager.appendObjects(2, events_objects);

	Px::ComponentBase* draw_objects[]{ &px, &btn_clear };
	drawmanager.appendObjects(2, draw_objects);


	while (!window.isShouldClose())
	{
		window.clearWindow(0.5f, 0.5f, 0.5f);
		Px::WindowEvents::UpdateTimer();
		drawmanager.drawAll();
		pxmanager.updateEvents(Px::deltaTime);
		lasti = px.getMouseRow();
		lastj = px.getMouseCol();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}


void drawMirrored(Px::PxCanvas& self, int lasti, int lastj, GLfloat r, GLfloat g, GLfloat b, int brushsize, int axes, bool symmetry)
{
	double angle = 360.0 / axes;
	glm::vec2 moveVec = glm::vec2(self.getMouseRow() - lasti, self.getMouseCol() - lastj);
	double moveVecLength = glm::length(moveVec);
	for (int k = 0; k < (int)ceil(moveVecLength); k++)
	{
		int newi = lasti + (moveVec.x / moveVecLength * k);
		int newj = lastj + (moveVec.y / moveVecLength * k);
		glm::vec2 center = glm::vec2(newi - ROWS / 2, newj - COLS / 2);
		double alpha_degree = glm::degrees(atan(center.x / center.y));
		if (newj < COLS / 2)
			alpha_degree += 180;
		double radius = glm::length(center);
		for (int axe = 0; axe < axes; axe++)
		{
			for (int brushi = -brushsize / 2; brushi <= brushsize / 2; brushi++)
			{
				for (int brushj = -brushsize / 2; brushj <= brushsize / 2; brushj++)
				{
					if (radius < ROWS / 2)
					{
						self.setPixel(ROWS / 2 + sin(glm::radians(alpha_degree + (angle * axe))) * radius + brushi,
							COLS / 2 + cos(glm::radians(alpha_degree + (angle * axe))) * radius + brushj, r, g, b);
						if (symmetry)
							self.setPixel(ROWS / 2 - sin(glm::radians(alpha_degree + (angle * axe - 45))) * radius + brushi,
								COLS / 2 + cos(glm::radians(alpha_degree + (angle * axe - 45))) * radius + brushj, r, g, b);
					}
				}
			}
		}
	}
}

*/