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
PxObj px(SIZEX, SIZEY, 800, 800);
double scale = 25.0f;
double step = 0.01;

double f(double x)
{
	return sin(x) * x;
}

int main()
{
	Window window(PxObj::WindowSizeX, PxObj::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	px.initCanvas(glm::make_mat4x3(colors), &shader);


	px.setLine(SIZEY / 2, 0, 0.5f, 0.5f, 0.5f, SIZEY / 2, SIZEX - 1, 1);
	px.setLine(0, SIZEX / 2, 0.5f, 0.5f, 0.5f, SIZEY - 1, SIZEX / 2, 1);

	for (double x = -SIZEX / 2.0 + 1; x < SIZEX / 2.0 - 1; x += step)
	{
		if (!isnan(f(x)))
		{
			px.setPixel(SIZEY - round(f(x/scale)*scale + SIZEY / 2.0), round(x + SIZEX / 2.0), 1.0f, 0.0f, 0.0f);
		}
	}

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
	PxObj::WindowSizeX = width;
	PxObj::WindowSizeY = height;
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
		px.setScale(1.0f);

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		px.increaseTranslate(-0.1, 0);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		px.increaseTranslate(0.1, 0);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		px.increaseTranslate(0, -0.1);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		px.increaseTranslate(0, 0.1);
}

*/