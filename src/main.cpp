#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader_s.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/useGLFM.cpp"
#include "../includes/PixelEngine.h"

/* create engine with set rows, cols, window width and height*/
PxEngine pxengine(80, 80, 800, 800);

int main()
{
	/* create window */
	initGLFWwindow("Game", PxEngine::WindowSizeX, PxEngine::WindowSizeY);

	/* create canvas and set background color */
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	PixelCanvasObj cvs(glm::make_mat4x3(colors), pxengine.getROWS(), pxengine.getCOLS());

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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
}