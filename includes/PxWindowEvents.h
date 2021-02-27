#pragma once
#include "windowGLFM.h"
#include "PixelEngine.h"

namespace Px
{

	class WindowEvents
	{
	public:
		static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);

		static void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos);

		static void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods);

		static void glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static void UpdateTimer();

	private:
		WindowEvents() { };
	};

}