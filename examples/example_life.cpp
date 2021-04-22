#include <iostream>
#include <ctime>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

const int ROWS = 400, COLS = 400;

enum Cells
{
	DIED,
	GREEN,
};

int arr[ROWS][COLS]{0};
int livesAround[ROWS][COLS]{0};

void randfillArr()
{
	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
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
	for (int i = 0; i < ROWS; ++i)
		for (int j = 0; j < ROWS; ++j)
			livesAround[i][j] = 0;

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			int AliveAround = 0;
			if (arr[i][j] != DIED)
				--AliveAround;
			for (int ki = -1; ki < 2; ++ki)
			{
				for (int kj = -1; kj < 2; ++kj)
				{
					int newi = ((i + ki) < 0) ? ROWS - 1 : ((i + ki) > ROWS - 1) ? 0
																				 : (i + ki);
					int newj = ((j + kj) < 0) ? COLS - 1 : ((j + kj) > COLS - 1) ? 0
																				 : (j + kj);
					if (arr[newi][newj] != DIED)
					{
						++AliveAround;
					}
				}
			}
			livesAround[i][j] = AliveAround;
		}
	}

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
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

bool pause = false;
void btn_pause_clbk(px::PxButton *btn)
{
	pause = !pause;
}

void btn_restrat_clbk(px::PxButton *btn)
{
	randfillArr();
}

int px::windowWidth = 800;
int px::windowHeight = 800;
Window window(px::windowWidth, px::windowHeight, "Game");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader *px::DefaultShader = &sh;

px::PxCanvas px_canvas(ROWS, COLS);
px::PxButton btn_pause(btn_pause_clbk, 0.04f, 0.04f, 0.5f, 0.9f, 0.9f);
px::PxButton btn_restrat(btn_restrat_clbk, 0.04f, 0.04f, 0.5f, 0.8f, 0.9f);

px::ManagerObjects manager{&px_canvas, &btn_pause, &btn_restrat};

void objectsEvents()
{
	if (px::isMouseLeftClick)
	{
		arr[px_canvas.getMouseRow()][px_canvas.getMouseCol()] = GREEN;
		px_canvas.setPixel(0.0f, 1.0f, 0.0f);
	}
	if (px::isMouseRightClick)
	{
		arr[px_canvas.getMouseRow()][px_canvas.getMouseCol()] = DIED;
		px_canvas.setPixel(0.0f, 0.0f, 0.0f);
	}

	if ((px_canvas.getScale() > 1.0f && px::mouseScrollY < 0) || (px_canvas.getScale() <= 5.0f && px::mouseScrollY > 0))
		px_canvas.IncreaseScale(px::mouseScrollY / 4.0f);
	if (px_canvas.getScale() < 1.0f)
		px_canvas.setScale(1.0f);
	px_canvas.setPosAtCenter();
	px::mouseScrollY = 0;
}

int main()
{
	srand(time(NULL));
	randfillArr();

	px_canvas.setUnderTextureColor(glm::mat4x3(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	px_canvas.setTextureOpacity(0.8f);

	btn_pause.setColorAsTexture(glm::vec3(0.0f, 0.0f, 0.8f));
	btn_restrat.setColorAsTexture(glm::vec3(0.0f, 1.0f, 0.8f));

	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		if (!pause)
		{
			clock_t start, end;
			start = clock();
			for (int i = 0; i < ROWS; ++i)
			{
				for (int j = 0; j < COLS; ++j)
				{
					if (arr[i][j] == GREEN)
						px_canvas.setPixel(i, j, 0.0f, 1.0f, 0.0f);
					else
						px_canvas.setPixel(i, j, 0.0f, 0.0f, 0.0f);
				}
			}

			update();
		}

		manager.drawAll();
		manager.updateAll();
		objectsEvents();

		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}