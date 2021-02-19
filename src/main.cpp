#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"

/* create engine with set rows, cols, window width and height*/
PxEngine pxengine(200, 200, 800, 800);

float scale = 2.0f;

int main()
{
	/* create window */
	Window window(PxEngine::WindowSizeX, PxEngine::WindowSizeY, "Game");

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelCanvasObj cvs(glm::make_mat4x3(colors), pxengine.getROWS(), pxengine.getCOLS());

	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* set zoom */
		cvs.setScale(scale);

		/* example of processing the left mouse button click */
		if (PxEngine::MouseLeftClick)
		{
			/* drawing in red color */
			pxengine.setPixel(pxengine.MousePosRow, pxengine.MousePosCol, 1.0f, 0.0f, 0.0f);
		}
		// PxEngine::MouseLeftClick = false; uncomment to disable continuous triggering. 

		/* start rendering*/
		/* setting a semi-transparent texture for background visibility  */
		cvs.setOpacity(0.2f);
		if (PxEngine::MouseRightClick)
		{
			/* rendering all layers while the right button pressed */
			cvs.draw(pxengine.getMixLayerCanvas());
		}
		else
		{
			/* rendering the current layer */
			cvs.draw(pxengine.getCanvas());
		}

		window.swapBuffers();
		window.poolEvents();
	}
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
	pxengine.MousePosCol = pxengine.TransformMouseXtoCol((int)xpos / scale + PxEngine::WindowSizeX / 2.0 / scale * (scale - 1));
	pxengine.MousePosRow = pxengine.TransformMouseYtoRow((int)ypos / scale + PxEngine::WindowSizeY / 2.0 / scale * (scale - 1));
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
	/* zoom with scrool */
	if ((yoffset > 0 && scale < 10.0) || (yoffset < 0 && scale > 0.5))
		scale += yoffset / 4.0f;
}

void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	/* closing the program when you press on escape */
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/* when you press enter, a new layer is created, you can switch to it and back using the arrows,
	the space bar deletes the current layer.
	Set it up as you need it or delete */
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
		pxengine.setLayer(pxengine.getCurrentLayer() + 1);
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
		pxengine.setLayer(pxengine.getCurrentLayer() - 1);
	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		pxengine.addLayer();
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		pxengine.deleteLayer(0);
	/* set base zoom */
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		scale = 1.0;
}