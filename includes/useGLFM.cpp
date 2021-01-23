#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
void glfwmouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
void glfwmouseClickCallback(GLFWwindow* window, int button, int action, int mods);
void glfwmouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLFWwindow* window;

void initGLFWwindow(const char* title, GLuint width, GLuint height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
	glfwSetCursorPosCallback(window, glfwmouseMoveCallback);
	glfwSetMouseButtonCallback(window, glfwmouseClickCallback);
	glfwSetScrollCallback(window, glfwmouseScrollCallback);
	glfwSetKeyCallback(window, glfwKeyCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	std::cout << "Render:" << std::string((const char*)glGetString(GL_RENDERER)) << std::endl;
	std::cout << "OpenGL:" << std::string((const char*)glGetString(GL_VERSION)) << std::endl;
}