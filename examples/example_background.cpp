#include <iostream>
#include <ctime>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

int px::windowWidth = 1280;
int px::windowHeight = 800;

Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader *px::DefaultShader = &sh;

int main()
{
	srand(time(NULL));
	Window window(px::windowWidth, px::windowHeight, "Game");

	float BgColor[12]{0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f};
	float colorChangeValue = 0.01f;
	px::PxBackground bg;
	bg.setUnderTextureColor(glm::make_mat4x3(BgColor));

	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		bg.setUnderTextureColor(glm::make_mat4x3(BgColor));

		for (int i = 0; i < 12; i += 1)
		{
			colorChangeValue = (((float)rand() / RAND_MAX * 2) - 1) / 50;
			BgColor[i] += colorChangeValue;
			if (BgColor[i] > 1.0f)
				BgColor[i] = 1.0f;
			if (BgColor[i] < 0.0f)
				BgColor[i] = 0.0f;
		}

		bg.draw();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}