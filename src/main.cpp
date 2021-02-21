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
PxObj px(100, 200, 800, 800, 1.0f, 0.5f);

int main()
{
	/* create window */
	Window window(PxObj::WindowSizeX, PxObj::WindowSizeY, "Game");

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	px.initCanvas(glm::make_mat4x3(colors), &shader);
	px.setScale(1.0f);
	px.setTranslate(0.5f, 0.2f);

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* example of processing the left mouse button click */
		if (PxObj::MouseLeftClick)
		{
			px.setPixel(px.MousePosRow, px.MousePosCol, 1.0f, 0.0f, 0.0f);
		}
		
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
	/* zoom with scrool */
	if ((yoffset > 0 && px.getScale() < 10.0) || (yoffset < 0 && px.getScale() > 0.4))
		px.increaseScale(yoffset / 4.0f);
}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/* closing the program when you press on escape */
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/* set base zoom */
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		px.setScale(1.0f);

	/* set pos */
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		px.increaseTranslate(0.1, 0);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		px.increaseTranslate(-0.1, 0);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		px.increaseTranslate(0, 0.1);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		px.increaseTranslate(0, -0.1);
}