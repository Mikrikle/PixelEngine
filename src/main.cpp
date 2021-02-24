#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"


Px::EventsDefaultManager pxmanager;

void btn_click(Px::ComponentMovable& obj)
{
	std::cout << "click!" << std::endl;
	obj.increaseScale(0.1f);
}

int main()
{
	Px::WindowSizeX = 800;
	Px::WindowSizeY = 800;
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");


	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Px::PxCanvas px(100, 200, 1.0f, 0.75f, glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, -0.25f);
	px.setMoveSpeed(3.0f);
	px.setMovable(Px::FULL);

	float BgColor[12]{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f };
	float colorChangeValue = 0.01f;
	Px::PxStaticBackground bg(glm::make_mat4x3(BgColor), &shader);

	float BtnColor[12]{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	Px::PxButton btn(0.25f, 0.25f, glm::make_mat4x3(BtnColor), &shader, 1.0f, 0.0f, 0.0f, btn_click, px);

	pxmanager.appendObj(px);
	pxmanager.appendObj(btn);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (!window.isShouldClose())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		bg.changeBackground(glm::make_mat4x3(BgColor));
		bg.draw();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		/* example of processing the left mouse button click */
		if (Px::MouseLeftClick)
		{
			px.setPixel(1.0f, 0.0f, 0.0f);
		}
		/* example of processing the right mouse button click */
		if (Px::MouseRightClick)
		{
			px.setPixel(0.0f, 0.0f, 0.0f);
		}

		/* example of change color */
		for (int i = 0; i < 12; i+=1)
		{
			if (BgColor[i] >= 0.9f || BgColor[i] <= -0.0f)
				colorChangeValue = -colorChangeValue;
			BgColor[i] += colorChangeValue;
		}
		

		/* setting the transparency of the texture relative to the background color */
		px.setOpacity(0.2f);
		px.draw();

		btn.draw();

		window.swapBuffers();
		window.poolEvents();
		pxmanager.updateEvents(deltaTime);
	}
	return 0;

}


void PxEvents::glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	Px::WindowSizeX = width;
	Px::WindowSizeY = height;
	glViewport(0, 0, width, height);
}

void PxEvents::glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
	Px::MousePosX = (int)xpos;
	Px::MousePosY = (int)ypos;
}

void PxEvents::glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods)
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

void PxEvents::glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	Px::ScrollX = (float)xoffset;
	Px::ScrollY = (float)yoffset;
}

void PxEvents::glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
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