#include "PxWindowEvents.h"
using namespace Px;

void WindowEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Px::WindowSizeX = width;
	Px::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void WindowEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	Px::MousePosX = (int)xpos;
	Px::MousePosY = (int)ypos;
}

void WindowEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			Px::MouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			Px::MouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			Px::MouseRightClick = true;
		else if (GLFW_RELEASE == action)
			Px::MouseRightClick = false;
	}
}

void WindowEvents::glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Px::ScrollX = (float)xoffset;
	Px::ScrollY = (float)yoffset;
}

void WindowEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Px::Keys[key] = true;
		else if (action == GLFW_RELEASE)
			Px::Keys[key] = false;
	}

}

void WindowEvents::UpdateTimer()
{
	float currentFrame = glfwGetTime();
	Px::deltaTime = currentFrame - Px::lastFrame;
	Px::lastFrame = currentFrame;
}