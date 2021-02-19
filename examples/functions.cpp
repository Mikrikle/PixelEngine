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
float scale = 1.0f;
PxEngine pxengine(SIZEY, SIZEX, 800, 800);



double f(double x)
{
	return x*x;
}

int main()
{
	Window window(PxEngine::WindowSizeX, PxEngine::WindowSizeY, "functions");

	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelCanvasObj cvs(glm::make_mat4x3(colors), pxengine.getROWS(), pxengine.getCOLS());


	pxengine.setLine(SIZEY / 2, 0, 0.5f, 0.5f, 0.5f, SIZEY / 2, SIZEX - 1, 1);
	pxengine.setLine(0, SIZEX / 2, 0.5f, 0.5f, 0.5f, SIZEY - 1, SIZEX / 2, 1);

	for (double x = -SIZEX / 2.0 + 1; x < SIZEX / 2.0 - 1; x += 0.01)
	{
		if (!isnan(f(x)))
		{
			pxengine.setPixel(SIZEY - round(f(x) + SIZEY / 2.0), round(x+ SIZEX / 2.0), 1.0f, 0.0f, 0.0f);
		}
	}

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		cvs.setOpacity(0.2f);
		cvs.setScale(scale);
		cvs.draw(pxengine.getCanvas());

		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
}

void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if ((yoffset > 0 && scale < 10.0) || (yoffset < 0 && scale > 0.5))
		scale += yoffset / 4.0f;
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		scale = 1.0;
}

*/