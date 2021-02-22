#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"


/* create main object */
/*       rows, cols, width, height, windowWidth, windowHeight*/
PixelCanvas px(100, 200, 1.0f, 0.75f, 1000, 800);
/*		the window size is set once */
PixelCanvas topPanel(1, 1, 1.0f, 0.25f);


int main()
{
	/* create window */
	Window window(PixelCanvas::WindowSizeX, PixelCanvas::WindowSizeY, "Game");

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	/* fast canvas init                              scale, X-offset, Y-offset */
	px.initCanvas(glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, -0.25f);

	float topPanelColor[12]{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f };
	float colorChangeValue = 0.01f;
	topPanel.initCanvas(glm::make_mat4x3(topPanelColor), &shader, 1.0f, 0.0f, 0.75f);

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* example of processing the left mouse button click */
		if (PixelCanvas::MouseLeftClick)
		{
			px.setPixel(px.MousePosRow, px.MousePosCol, 1.0f, 0.0f, 0.0f);
		}
		/* example of processing the right mouse button click */
		if (PixelCanvas::MouseRightClick)
		{
			px.setPixel(px.MousePosRow, px.MousePosCol, 0.0f, 0.0f, 0.0f);
		}

		/* example of change color */
		for (int i = 0; i < 12; i+=1)
		{
			if (topPanelColor[i] >= 0.9f || topPanelColor[i] <= -0.1f)
				colorChangeValue = -colorChangeValue;
			topPanelColor[i] += colorChangeValue;
		}
		topPanel.changeBackground(glm::make_mat4x3(topPanelColor));

		/* setting the transparency of the texture relative to the background color */
		px.setOpacity(0.2f);
		px.draw();

		/* fully transparent texture */
		topPanel.setOpacity(1.0f);
		topPanel.draw();

		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}


void PxEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	PixelCanvas::WindowSizeX = width;
	PixelCanvas::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void PxEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	px.TransformMousePosToGrid((int)xpos, (int)ypos);
}

void PxEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			PixelCanvas::MouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			PixelCanvas::MouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			PixelCanvas::MouseRightClick = true;
		else if (GLFW_RELEASE == action)
			PixelCanvas::MouseRightClick = false;
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
		px.increaseTranslate(0.1f, 0.0f);
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		px.increaseTranslate(-0.1f, 0.0f);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		px.increaseTranslate(0.0f, 0.1f);
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		px.increaseTranslate(0.0f, -0.1f);
}