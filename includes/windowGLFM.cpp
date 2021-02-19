#include "windowGLFM.h"

Window::Window(int WIDTH, int HEIGHT, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetCursorPosCallback(window, glfwmouseMoveCallback);
	glfwSetMouseButtonCallback(window, glfwmouseClickCallback);
	glfwSetScrollCallback(window, glfwmouseScrollCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);

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

GLFWwindow* Window::getWindow()
{
	return this->window;
}

