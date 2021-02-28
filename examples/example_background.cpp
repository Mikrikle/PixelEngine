/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <ctime>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"
#include "../includes/PxWindowEvents.h"



int main()
{
	srand(time(NULL));
	Px::WindowSizeX = 1280;
	Px::WindowSizeY = 800;
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");



	float BgColor[12]{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f };
	float colorChangeValue = 0.01f;
	Px::PxStaticBackground bg(glm::make_mat4x3(BgColor), &shader);

	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		bg.changeBackground(glm::make_mat4x3(BgColor));

		for (int i = 0; i < 12; i += 1)
		{
			colorChangeValue = (((float)rand() / RAND_MAX * 2) - 1)/50;
			BgColor[i] += colorChangeValue;
			if (BgColor[i] > 1.0f)
				BgColor[i] = 1.0f;
			if(BgColor[i]  < 0.0f)
				BgColor[i] = 0.0f;
		}

		bg.draw();
		window.swapBuffers();
		window.poolEvents();

	}
	return 0;

}

*/