#include <iostream>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

// set your window size and name
int px::windowWidth = 800;
int px::windowHeight = 800;
Window window(px::windowWidth, px::windowHeight, "App_name");

// selecet shader and bind it with px
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

// create your app
// you can use PxBaseApp or your own classes
class App : public px::PxBaseApp
{
public:
	App()
	{
		// all objects list
		manager.init({ &test_r, &color_slider, &colored_rectangle, &isShowRound, &isSliderWork, &cvs });

		// place objects on the grid
		grid.init(3, 3, {
			{&cvs, 1, 3},
			{&isSliderWork}, {&central_grid}, {&isShowRound},
			{&color_slider, 1, 3} }
		);

		// after creating a grid and a list of objects, the application can be initialized
		init();
	}

	// called on each iteration of the main loop
	void objectsEvents()
	{
		// allows you to define the behavior of objects when updating
		if (cvs.isClickOn())
		{
			cvs.setPixel(1.0f, 0.2f, 0.1f);
		}
		if (px::keyboardKeys[GLFW_KEY_SPACE])
		{
			cvs.fillBlack();
		}
	}

	// called at once when app is inited
	void objectsSetting()
	{
		// set objects property here
		test_r.setImgTexture("../../src/includes/textures/round.png");
		test_r.setTextureOpacity(1.0f);
		colored_rectangle.setTextureOpacity(1.0f);
		colored_rectangle.setColorAsTexture(0.0f, color_slider.getPercentages() / 100.0f, 0.0f);
		isShowRound.setColorAsTexture(0.5f, 0.0f, 0.0f);
		isSliderWork.setUnderTextureColor(glm::mat4x3(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f));
		cvs.setTextureOpacity(0.9f);
		// by default, the created widgets are disabled
		// specify this if you want to create a widget in the active position
		isShowRound.setActive(true);
		isSliderWork.setActive(true);
		// widgets are created from simpler classes
		// to change a specific part of the widget, contact it directly
		color_slider.toggle_route_line.setColorAsTexture(0.0f, 1.0f, 0.0f);
		color_slider.setToggleWidth(0.2f);
		color_slider.setToggleRouteLineHeight(0.2f);
	}

private:
	// create objects here

	px::PxSlider color_slider{ [this](px::PxSlider* self) {
		colored_rectangle.setColorAsTexture(0.0f, self->getPercentages() / 100.0f, 0.0f);
	} };

	px::PxCheckBox isShowRound{ [this](px::PxCheckBox* self) {
		if (self->isActive())
		{
			manager.addToIgnoreDrawingLsist(0);
		}
		else
		{
			manager.removeFromIgnoreDrawingList(0);
		}
	} };

	px::PxSwitch isSliderWork{ [this](px::PxSwitch* self) {
		if (self->isActive())
		{
			manager.addToIgnoreUpdatingLsist(1);
			color_slider.toggle_route_line.setColorAsTexture(1.0f, 0.0f, 0.0f);
		}
		else
		{
			manager.removeFromIgnoreUpdatingList(1);
			color_slider.toggle_route_line.setColorAsTexture(0.0f, 1.0f, 0.0f);
		}
	} };

	px::PxCanvas cvs{100, 300};
	px::PxRectangle colored_rectangle;
	px::PxRectangle test_r;
	px::GridLayout central_grid{ 2, 1, { {&test_r}, {&colored_rectangle} } };
};

int main()
{	
	px::PxButton a;
	App TestApp;
	window.enable_blend(); // need for transparent texture
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f); // background color
		TestApp.run();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}