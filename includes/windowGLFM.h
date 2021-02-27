#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* window;
public:

	Window(int WIDTH, int HEIGHT, const char* title);

	~Window();

	bool isShouldClose();

	void swapBuffers();

	void poolEvents();

	void clearWindow(float r, float g, float b);

	GLFWwindow* getWindow();

};