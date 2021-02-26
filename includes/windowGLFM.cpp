#include "windowGLFM.h"
#include "PixelEngine.h"

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

void  Window::clearWindow(float r, float g, float b)
{
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
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
