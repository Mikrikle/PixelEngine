#include <iostream>
#include <fstream>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

int px::windowWidth = 800;
int px::windowHeight = 800;

Window window(px::windowWidth, px::windowHeight, "Game");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

class App : public px::PxBaseApp
{
public:
	App()
	{
		init();
		manager.init({ &test_r, &color_slider, &colored_rectangle });
		grid.init(3, 3, { 
			{nullptr, 1, 3},
			{}, {&px::GridLayout(2, 1, { {&test_r}, {&colored_rectangle} })}, {},
			{&color_slider, 1, 3} }
		);
	}

	void objectsEvents()
	{
		
	}

	void objectsSetting()
	{
		test_r.setImgTexture("../../src/includes/textures/round.png");
		test_r.setTextureOpacity(1.0f);
		colored_rectangle.setTextureOpacity(1.0f);
	}

private:
	px::PxSlider color_slider{ [this](px::PxSlider *self) {colored_rectangle.setColorAsTexture(0.0f, self->getPercentages() / 100.0f, 0.0f); }};
	px::PxRectangle colored_rectangle;
	px::PxRectangle test_r;
};

int main()
{
	float colorChangeValue = 0.01f;
	App TestApp;
	window.enable_blend();
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);
		TestApp.update();
		TestApp.draw();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}