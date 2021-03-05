/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ctime>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"
#include "../includes/PxWindowEvents.h"


const int ROWS = 400, COLS = 400;

enum Cells
{
	DIED, GREEN,
};

int arr[ROWS][COLS]{ 0 };
int livesAround[ROWS][COLS]{ 0 };

void randfillArr()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (rand() % 9 == 1)
			{
				arr[i][j] = GREEN;
			}
			else
			{
				arr[i][j] = DIED;
			}
		}
	}
}

void update()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < ROWS; j++)
			livesAround[i][j] = 0;

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int AliveAround = 0;
			if (arr[i][j] != DIED)
				AliveAround--;
			for (int ki = -1; ki < 2; ki++)
			{
				for (int kj = -1; kj < 2; kj++)
				{
					int newi = ((i + ki) < 0) ? ROWS - 1 : ((i + ki) > ROWS - 1) ? 0 : (i + ki);
					int newj = ((j + kj) < 0) ? COLS - 1 : ((j + kj) > COLS - 1) ? 0 : (j + kj);
					if (arr[newi][newj] != DIED)
					{
						AliveAround++;
					}
				}
			}
			livesAround[i][j] = AliveAround;
		}
	}

	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (arr[i][j] == GREEN && (livesAround[i][j] < 2 || livesAround[i][j] > 3))
			{
				arr[i][j] = DIED;
			}
			else if (arr[i][j] == DIED && livesAround[i][j] == 3)
			{
				arr[i][j] = GREEN;
			}
		}
	}
}

Px::EventsDefaultManager pxmanager;
Px::DrawManager drawmanager;

bool pause = false;
void btn_pause_clbk()
{
	pause = !pause;
}

void btn_restrat_clbk()
{
	randfillArr();
}

void event_px_on_click(Px::PxCanvas& self)
{
	if (Px::MouseLeftClick)
	{
		arr[self.getMouseRow()][self.getMouseCol()] = GREEN;
		self.setPixel(0.0f, 1.0f, 0.0f);
	}
	if (Px::MouseRightClick)
	{
		arr[self.getMouseRow()][self.getMouseCol()] = DIED;
		self.setPixel(0.0f, 0.0f, 0.0f);
	}
	
}

void event_px_scroll(Px::PxCanvas& self)
{
	if ((self.getScale() > 1.0f && Px::ScrollY < 0) || (self.getScale() <= 5.0f && Px::ScrollY > 0))
		self.increaseScale(Px::ScrollY / 4.0f);
	if (self.getScale() < 1.0f)
		self.setScale(1.0f);
	Px::ScrollY = 0;
}

int main()
{
	Px::WindowSizeX = 800;
	Px::WindowSizeY = 800;
	srand(time(NULL));
	randfillArr();
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Px::PxCanvas px(ROWS, COLS, 1.0f, 1.0f, glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, 0.0f, event_px_on_click, event_px_scroll, nullptr);
	px.setOpacity(0.2f);

	float btn_pause_colors[6]{ 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.6f };
	Px::PxButton btn_pause(0.04f, 0.04f, glm::make_mat2x3(btn_pause_colors), &shader, 1.0f, 0.9f, 0.9f, btn_pause_clbk);

	float btn_restart_colors[6]{ 0.0f, 1.0f, 0.8f, 0.0f, 0.5f, 0.6f };
	Px::PxButton btn_restrat(0.04f, 0.04f, glm::make_mat2x3(btn_restart_colors), &shader, 1.0f, 0.8f, 0.9f, btn_restrat_clbk);

	Px::ComponentEvents* events_objects[]{ &px, &btn_pause, &btn_restrat };
	pxmanager.appendObjects(3, events_objects);

	Px::ComponentBase* draw_objects[]{ &px, &btn_pause, &btn_restrat };
	drawmanager.appendObjects(3, draw_objects);


	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		if (!pause)
		{
			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < COLS; j++)
				{
					if (arr[i][j] == GREEN)
						px.setPixel(i, j, 0.0f, 1.0f, 0.0f);
					else
						px.setPixel(i, j, 0.0f, 0.0f, 0.0f);
				}
			}

			update();
		}

		drawmanager.drawAll();
		pxmanager.updateEvents(Px::deltaTime);
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}

*/

