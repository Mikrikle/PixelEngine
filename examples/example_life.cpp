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

const int ROWS = 400, COLS = 400;
PxObj px(ROWS, COLS, 800, 800, 2.0f, 2.0f);

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
}


int main()
{
	srand(time(NULL));
	randfillArr();
	Window window(PxObj::WindowSizeX, PxObj::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	px.initCanvas(glm::make_mat4x3(colors), &shader);

	bool pause = false;
	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (!pause)
		{
			update();
		}

		
		if (PxObj::MouseLeftClick)
		{
			arr[px.MousePosRow][px.MousePosCol] = GREEN;
			px.setPixel(px.MousePosRow, px.MousePosCol, 0.0f, 1.0f, 0.0f);
		}
		if (PxObj::MouseRightClick)
		{
			pause = !pause;
		}
		PxObj::MouseRightClick = false;

		px.setOpacity(0.2f);
		px.draw();

		window.swapBuffers();
		glfwPollEvents();
	}
	return 0;

}


void PxEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	PxObj::WindowSizeX = width;
	PxObj::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void PxEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	px.TransformMouseXtoGrid((int)xpos, (int)ypos);
}

void PxEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			PxObj::MouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			PxObj::MouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			PxObj::MouseRightClick = true;
		else if (GLFW_RELEASE == action)
			PxObj::MouseRightClick = false;
	}
}

void PxEvents::glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		randfillArr();
}

*/