#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"

/* create engine with set rows, cols, window width and height*/
PxObj px(80, 80, 800, 800);
PxObj px2(10, 10, 800, 800);

float scale = 0.5f;
float tx = 0.5f, ty = 0.5f;

float scale2 = 0.5f;
float tx2 = -0.3f, ty2 = -0.3f;

int main()
{
	/* create window */
	Window window(PxObj::WindowSizeX, PxObj::WindowSizeY, "Game");

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	px.initCanvas(glm::make_mat4x3(colors), &shader);
	px2.initCanvas(glm::make_mat4x3(colors), &shader);

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* set zoom */
		px.setScale(scale);
		px.setTranslate(tx, ty);

		px2.setScale(scale2);
		px2.setTranslate(tx2, ty2);

		/* example of processing the left mouse button click */
		if (PxObj::MouseLeftClick)
		{
			if(px.MousePosRow >=0 && px.MousePosCol >= 0)
				px.setPixel(px.MousePosRow, px.MousePosCol, 1.0f, 0.0f, 0.0f);
			else
				px2.setPixel(px2.MousePosRow, px2.MousePosCol, 1.0f, 0.0f, 0.0f);
		}

		px2.setOpacity(0.5f);
		px2.draw();

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
	px.TransformMouseXtoCol((int)xpos);
	px.TransformMouseYtoRow((int)ypos);
	px2.TransformMouseXtoCol((int)xpos);
	px2.TransformMouseYtoRow((int)ypos);
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
	if ((yoffset > 0 && scale < 10.0) || (yoffset < 0 && scale > 0.5))
		scale += yoffset / 4.0f;
}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/* closing the program when you press on escape */
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/* set base zoom */
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		scale = 1.0;

	/* set pos */
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		tx += 0.1;
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		tx -= 0.1;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		ty += 0.1;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		ty -= 0.1;
}