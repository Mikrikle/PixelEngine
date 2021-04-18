#include "windowGLFM.h"

Window::Window(int width, int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwSetWindowSizeCallback(window, px::WindowEvents::glfwWindowSizeCallback);
	glfwSetCursorPosCallback(window, px::WindowEvents::glfwmouseMoveCallback);
	glfwSetMouseButtonCallback(window, px::WindowEvents::glfwmouseClickCallback);
	glfwSetScrollCallback(window, px::WindowEvents::glfwmouseScrollCallback);
	glfwSetKeyCallback(window, px::WindowEvents::glfwKeyCallback);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	std::cout << "Render:" << std::string((const char*)glGetString(GL_RENDERER)) << std::endl;
	std::cout << "OpenGL:" << std::string((const char*)glGetString(GL_VERSION)) << std::endl;
	glViewport(0, 0, width, height);
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::isShouldClose()
{
	return (bool)glfwWindowShouldClose(window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(window);
}

void Window::poolEvents()
{
	if (!px::isMouseLeftClick)
	{
		px::isMouseAlreadyUsed = false;
	}
	px::WindowEvents::UpdateTimer();
	glfwPollEvents();
}

GLFWwindow* Window::getWindow()
{
	return this->window;
}

void Window::clearWindow(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::enable_blend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}