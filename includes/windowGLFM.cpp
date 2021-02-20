#include "windowGLFM.h"

Window::Window(int WIDTH, int HEIGHT, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

	glfwSetWindowSizeCallback(window, PxEvents::glfwWindowSizeCallback);
	glfwSetCursorPosCallback(window, PxEvents::glfwmouseMoveCallback);
	glfwSetMouseButtonCallback(window, PxEvents::glfwmouseClickCallback);
	glfwSetScrollCallback(window, PxEvents::glfwmouseScrollCallback);
	glfwSetKeyCallback(window, PxEvents::glfwKeyCallback);

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
	glViewport(0, 0, WIDTH, HEIGHT);
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
	glfwPollEvents();
}

GLFWwindow* Window::getWindow()
{
	return this->window;
}

