#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader_s.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/Engine.cpp"
#include "../includes/useGLFM.cpp"


int main()
{
	initGLFWwindow("Game", WindowSizeX, WindowSizeY);
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelDraw game(glm::make_mat4x3(colors));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (MouseLeftClick)
		{
			setPixel(pixelCanvas, MousePosRow, MousePosCol, 1.0f, 0.0f, 0.0f);
		}

		game.setOpacity(0.2f);
		game.draw(pixelCanvas);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}


void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	WindowSizeX = width;
	WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	MousePosCol = TransformMouseXtoCol(((int)xpos > ROWS) ? (ROWS - 1) : ((int)xpos < 0) ? 0 : (int)xpos);
	MousePosRow = TransformMouseYtoRow(((int)ypos > COLS) ? (COLS - 1) : ((int)ypos < 0) ? 0 : (int)ypos);
}

void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
			MouseLeftClick = true;
		else if (GLFW_RELEASE == action)
			MouseLeftClick = false;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
			MouseRightClick = true;
		else if (GLFW_RELEASE == action)
			MouseRightClick = false;
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