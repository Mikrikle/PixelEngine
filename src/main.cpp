#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader_s.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/useGLFM.cpp"
#include "../includes/PixelEngine.h"

int WindowWidth = 800, WindowHeight = 800;
int ROWS = 80, COLS = 80;
PxEngine pxengine(ROWS, COLS, WindowWidth, WindowHeight);

int main()
{
	initGLFWwindow("Game", PxEngine::WindowSizeX, PxEngine::WindowSizeY);
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelCanvasObj cvs(glm::make_mat4x3(colors), pxengine.getROWS(), pxengine.getCOLS());

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (PxEngine::MouseLeftClick)
		{
			pxengine.setPixel(pxengine.MousePosRow, pxengine.MousePosCol, 1.0f, 0.0f, 0.0f);
		}

		cvs.setOpacity(0.2f);
		if (PxEngine::MouseRightClick)
		{
			cvs.draw(pxengine.getMixLayerCanvas());
		}
		else
		{
			cvs.draw(pxengine.getCanvas());
		}

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
	pxengine.MousePosCol = pxengine.TransformMouseXtoCol((int)xpos);
	pxengine.MousePosRow = pxengine.TransformMouseYtoRow((int)ypos);
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
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		pxengine.setLayer(pxengine.getCurrentLayer() + 1);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		pxengine.setLayer(pxengine.getCurrentLayer() - 1);
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		pxengine.addLayer();
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		pxengine.deleteLayer(0);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		std::cout << pxengine.getCurrentLayer() << std::endl;
}