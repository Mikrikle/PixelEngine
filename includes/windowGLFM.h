#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods);
void glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

class Window
{
private:
	GLFWwindow* window;
public:

	Window(int WIDTH, int HEIGHT, const char* title);

	~Window();

	bool isShouldClose();

	void swapBuffers();

	GLFWwindow* getWindow();

};