#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader_s.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/Engine.cpp"
#include "../includes/useGLFM.cpp"

PxEngine pxengine(50, 50, 800, 800);

int main()
{
	initGLFWwindow("Game", PxEngine::WindowSizeX, PxEngine::WindowSizeY);
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelDraw cvs(glm::make_mat4x3(colors), pxengine.ROWS, pxengine.COLS);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (PxEngine::MouseLeftClick)
		{
			pxengine.setPixel(pxengine.MousePosRow, pxengine.MousePosCol, 1.0f, 0.0f, 0.0f);
		}

		cvs.setOpacity(0.2f);
		cvs.draw(pxengine.getCanvas());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	PxEngine::WindowSizeX = width;
	PxEngine::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	pxengine.MousePosCol = pxengine.TransformMouseXtoCol(((int)xpos > PxEngine::WindowSizeY) ? (PxEngine::WindowSizeY - 1) : ((int)xpos < 0) ? 0 : (int)xpos);
	pxengine.MousePosRow = pxengine.TransformMouseYtoRow(((int)ypos > PxEngine::WindowSizeX) ? (PxEngine::WindowSizeX - 1) : ((int)ypos < 0) ? 0 : (int)ypos);
}

void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			PxEngine::MouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			PxEngine::MouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			PxEngine::MouseRightClick = true;
		else if (GLFW_RELEASE == action)
			PxEngine::MouseRightClick = false;
	}
}

void glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}