#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"

/* create with set rows, cols, window width and height*/
const int arrsize = 2;
PxObj PxObjArr[arrsize] = { {80, 80, 800, 800},{10, 10, 800, 800} };

int main()
{
	/* create window */
	Window window(PxObj::WindowSizeX, PxObj::WindowSizeY, "Game");

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	PxObjArr[0].initCanvas(glm::make_mat4x3(colors), &shader);
	PxObjArr[0].setScale(0.5f);
	PxObjArr[0].setTranslate(0.5f, 0.5f);
	PxObjArr[1].initCanvas(glm::make_mat4x3(colors), &shader);
	PxObjArr[1].setScale(0.4f);
	PxObjArr[1].setTranslate(-0.3f, -0.3f);

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* example of processing the left mouse button click */
		if (PxObj::MouseLeftClick)
		{
			for (int i = 0; i < arrsize; i++)
			{
				if (PxObjArr[i].MousePosRow >= 0 && PxObjArr[i].MousePosCol >= 0)
				{
					PxObjArr[i].setPixel(PxObjArr[i].MousePosRow, PxObjArr[i].MousePosCol, 1.0f, 0.0f, 0.0f);
					break;
				}
			}

		}

		for (int i = arrsize-1; i >= 0; i--)
		{
			PxObjArr[i].setOpacity(0.2f);
			PxObjArr[i].draw();
		}


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
	for (int i = 0; i < arrsize; i++)
	{
		PxObjArr[i].TransformMouseXtoCol((int)xpos);
		PxObjArr[i].TransformMouseYtoRow((int)ypos);
	}
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
	/* zoom with scrool */
	if ((yoffset > 0 && PxObjArr[0].getScale() < 10.0) || (yoffset < 0 && PxObjArr[0].getScale() > 0.4))
		PxObjArr[0].increaseScale(yoffset / 4.0f);
}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/* closing the program when you press on escape */
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/* set base zoom */
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		PxObjArr[0].setScale(1.0f);

	/* set pos */
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		PxObjArr[0].increaseTranslate(0.1, 0);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		PxObjArr[0].increaseTranslate(-0.1, 0);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		PxObjArr[0].increaseTranslate(0, 0.1);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		PxObjArr[0].increaseTranslate(0, -0.1);
}