#include "PixelEngine.h"
using namespace px;

void WindowEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	px::windowWidth = width;
	px::windowHeight = height;
	glViewport(0, 0, width, height);
}

void WindowEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	px::mousePosX = static_cast<int> (xpos);
	px::mousePosY = static_cast<int> (ypos);
	absoluteMousePosX = (px::mousePosX / (px::windowWidth / 2.0f)) - 1.0f;
	absoluteMousePosY = ((px::windowHeight - px::mousePosY) / (px::windowHeight / 2.0f)) - 1.0f;
}

void WindowEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			px::isMouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			px::isMouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			px::isMouseRightClick = true;
		else if (GLFW_RELEASE == action)
			px::isMouseRightClick = false;
	}
}

void WindowEvents::glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	px::mouseScrollX = static_cast<float> (xoffset);
	px::mouseScrollY = static_cast<float> (yoffset);
}

void WindowEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			px::keyboardKeys[key] = true;
		else if (action == GLFW_RELEASE)
			px::keyboardKeys[key] = false;
	}
}

void WindowEvents::UpdateTimer()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	px::deltaTime = currentFrame - px::lastFrameTime;
	px::lastFrameTime = currentFrame;
}