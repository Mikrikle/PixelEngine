/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"

int SIZEX = 800;
int SIZEY = SIZEX;
PxPixelCanvas px(SIZEX, SIZEY, 1.0f, 1.0f, 800, 800);
double scale = 30.0f;
double step = 0.005;

double f(double x)
{
	return cos(sin(x) * x) * tan(x);
}

void render()
{
	for (int i = SIZEX/2, j= SIZEX / 2; i < SIZEX; i += scale, j-= scale)
	{
		px.setLine(0, i, 0.1f, 0.1f, 0.1f, SIZEY - 1, i, 1);
		px.setLine(0, j, 0.1f, 0.1f, 0.1f, SIZEY - 1, j, 1);
	}
	for (int i = SIZEY/2, j = SIZEX / 2; i < SIZEY; i += scale, j-=scale)
	{
		px.setLine(i, 0, 0.1f, 0.1f, 0.1f, i, SIZEX - 1, 1);
		px.setLine(j, 0, 0.1f, 0.1f, 0.1f, j, SIZEX - 1, 1);
	}
	px.setLine(SIZEY / 2, 0, 0.5f, 0.5f, 0.5f, SIZEY / 2, SIZEX - 1, 1);
	px.setLine(0, SIZEX / 2, 0.5f, 0.5f, 0.5f, SIZEY - 1, SIZEX / 2, 1);

	for (double x = -SIZEX / 2.0 + 1; x < SIZEX / 2.0 - 1; x += step)
	{
		if (!isnan(f(x)))
		{
			px.setPixel(SIZEY - round(f(x / scale) * scale + SIZEY / 2.0), round(x + SIZEX / 2.0), 1.0f, 0.0f, 0.0f);
		}
	}
}

int main()
{
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	px.initCanvas(glm::make_mat4x3(colors), &shader);


	render();

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		px.setOpacity(0.2f);
		px.draw();

		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}


void PxEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Px::WindowSizeX = width;
	Px::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void PxEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
}

void PxEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void PxEvents::glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if ((yoffset > 0 && px.getScale() < 10.0) || (yoffset < 0 && px.getScale() > 1))
		px.increaseScale(yoffset / 4.0f);
}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		px.setScale(1.0f);
		px.setTranslate(0.0f, 0.0f);
	}

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		px.increaseTranslate(-0.1, 0);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		px.increaseTranslate(0.1, 0);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		px.increaseTranslate(0, -0.1);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		px.increaseTranslate(0, 0.1);
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		if(scale<100)
			scale += 5;
		px.clear();
		render();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		if (scale > 6)
			scale -= 5;
		px.clear();
		render();
	}
}

*/