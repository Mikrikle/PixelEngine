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
	WHITE, BLACK,
};

typedef struct
{
	int posROW;
	int posCOL;
	int directionROW;
	int directionCOL;
} Ant;
Ant ant{ ROWS / 2, COLS / 2, -1, 0 };

int arr[ROWS][COLS]{ 0 };
int livesAround[ROWS][COLS]{ 0 };

void fillArr()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			arr[i][j] = WHITE;
		}
	}

}

void turnleft()
{
	if (ant.directionROW == -1 && ant.directionCOL == 0)
	{
		ant.directionROW = 0;
		ant.directionCOL = -1;
	}
	else if (ant.directionROW == 1 && ant.directionCOL == 0)
	{
		ant.directionROW = 0;
		ant.directionCOL = 1;
	}
	else if (ant.directionROW == 0 && ant.directionCOL == -1)
	{
		ant.directionROW = 1;
		ant.directionCOL = 0;
	}
	else if (ant.directionROW == 0 && ant.directionCOL == 1)
	{
		ant.directionROW = -1;
		ant.directionCOL = 0;
	}
}

void turnright()
{
	if (ant.directionROW == -1 && ant.directionCOL == 0)
	{
		ant.directionROW = 0;
		ant.directionCOL = 1;
	}
	else if (ant.directionROW == 1 && ant.directionCOL == 0)
	{
		ant.directionROW = 0;
		ant.directionCOL = -1;
	}
	else if (ant.directionROW == 0 && ant.directionCOL == -1)
	{
		ant.directionROW = -1;
		ant.directionCOL = 0;
	}
	else if (ant.directionROW == 0 && ant.directionCOL == 1)
	{
		ant.directionROW = 1;
		ant.directionCOL = 0;
	}
}

void update()
{
	if (arr[ant.posROW][ant.posCOL] == BLACK)
	{
		turnleft();
		arr[ant.posROW][ant.posCOL] = WHITE;
	}
	else if (arr[ant.posROW][ant.posCOL] == WHITE)
	{
		turnright();
		arr[ant.posROW][ant.posCOL] = BLACK;
	}

	ant.posROW += ant.directionROW;
	ant.posCOL += ant.directionCOL;
	if (ant.posCOL < 0)
		ant.posCOL = COLS - 1;
	if (ant.posCOL > COLS - 1)
		ant.posCOL = 0;
	if (ant.posROW < 0)
		ant.posROW = ROWS - 1;
	if (ant.posROW > ROWS - 1)
		ant.posROW = 0;
}

Px::EventsDefaultManager pxmanager;
Px::DrawManager drawmanager;

bool pause = false;


void event_px_scroll(Px::PxCanvas& self)
{
	if ((self.getScale() > 1.0f && Px::ScrollY < 0) || (self.getScale() <= 5.0f && Px::ScrollY > 0))
		self.increaseScale(Px::ScrollY / 4.0f);
	if (self.getScale() < 1.0f)
		self.setScale(1.0f);
	Px::ScrollY = 0;
}

void event_px_on_click(Px::PxCanvas& self)
{
	if (Px::MouseLeftClick)
	{
		pause = !pause;
	}
	if (Px::MouseRightClick)
	{
		ant.posROW = ROWS / 2;
		ant.posCOL = COLS / 2;
		fillArr();
	}
	Px::MouseLeftClick = false;
	Px::MouseRightClick = false;
}

int main()
{
	Px::WindowSizeX = 800;
	Px::WindowSizeY = 800;
	srand(time(NULL));
	fillArr();
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[6]{ 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	Px::PxCanvas px(ROWS, COLS, 1.0f, 1.0f, glm::make_mat2x3(colors), &shader, 1.0f, 0.0f, 0.0f, event_px_on_click, event_px_scroll, nullptr);
	px.setOpacity(0.2f);


	Px::ComponentEvents* events_objects[]{ &px };
	pxmanager.appendObjects(1, events_objects);

	Px::ComponentBase* draw_objects[]{ &px };
	drawmanager.appendObjects(1, draw_objects);

	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		if (!pause)
		{
			for (int i = 0; i < ROWS; i++)
			{
				for (int j = 0; j < COLS; j++)
				{
					if (arr[i][j] == WHITE)
						px.setPixel(i, j, 1.0f, 1.0f, 1.0f);
					else
						px.setPixel(i, j, 0.0f, 0.0f, 0.0f);
				}
			}
			px.setPixel(ant.posROW, ant.posCOL, 1.0f, 0.0f, 0.0f);
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