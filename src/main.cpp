#include <iostream>
#include <fstream>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

int px::windowWidth = 800;
int px::windowHeight = 800;

Window window(px::windowWidth, px::windowHeight, "Game");

Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

px::PxRectangle test_r;
px::GridLayout test_grl(1, 1, {{&test_r}});
px::ManagerObjects manager{&test_grl};

void objectsSetting()
{
	test_r.setImgTexture("../../src/includes/textures/round.png");
	test_r.setTextureOpacity(1.0f);
}

void objectsEvents()
{
}

int main()
{
	objectsSetting();
	float colorChangeValue = 0.01f;

	window.enable_blend();
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);
		manager.updateAll();
		objectsEvents();
		manager.drawAll();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}
