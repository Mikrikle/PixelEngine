#include "windowGLFM.h"
#include "PxWindowEvents.h"

Window::Window(int WIDTH, int HEIGHT, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	this->window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);

	glfwSetWindowSizeCallback(window, Px::WindowEvents::glfwWindowSizeCallback);
	glfwSetCursorPosCallback(window, Px::WindowEvents::glfwmouseMoveCallback);
	glfwSetMouseButtonCallback(window, Px::WindowEvents::glfwmouseClickCallback);
	glfwSetScrollCallback(window, Px::WindowEvents::glfwmouseScrollCallback);
	glfwSetKeyCallback(window, Px::WindowEvents::glfwKeyCallback);

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
	Px::WindowEvents::UpdateTimer();
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