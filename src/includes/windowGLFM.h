#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "PixelEngine.h"

namespace px
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

class Window
{
private:
	GLFWwindow* window;
public:

	Window(int width, int height, const char* title);

	~Window();

	bool isShouldClose();

	void swapBuffers();

	void poolEvents();

	void clearWindow(float r, float g, float b);

	void enable_blend();

	GLFWwindow* getWindow();
};