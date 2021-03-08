#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"
#include "../includes/PxWindowEvents.h"


void btn_click(Px::PxButton* btn);

int Px::WindowSizeX = 800;
int Px::WindowSizeY = 800;


Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");


float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
float BgColor[12]{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f };
float BtnColor[6]{ 0.0f, 0.0f, 0.0f, 0.6f, 0.0f, 0.0f, };

Px::PxCanvas px(100, 200, 0.75f, 0.5f, glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, -0.25f);
Px::PxBackground bg(glm::make_mat4x3(BgColor), &shader);
Px::PxButton clear_btn(0.05f, 0.05f, glm::make_mat2x3(BtnColor), &shader, 1.0f, 0.9f, 0.9f, btn_click);

Px::PxRegularPolygon figure(0.125f, 6, glm::make_mat2x3(BtnColor), &shader, 1.0f, -0.5f, -0.5f);

Px::ObjectManager manager;
Px::ComponentBase* all_objects[]{ &bg, &px, &clear_btn, &figure };


void btn_click(Px::PxButton* btn)
{
	px.clear();
}

void objectsSetting()
{
	manager.appendObjects(sizeof(all_objects) / sizeof(all_objects[0]), all_objects);
	px.setOpacity(0.2f);
	clear_btn.setBaseColor(0.0f, 0.0f, 0.5f);
	clear_btn.setOpacity(0.8f);
}

void objectsEvents()
{
	if (px.isClickOn())
	{
		px.setPixel(1.0f, 0.0f, 0.0f);
	}

	if (Px::Keys[GLFW_KEY_W])
		px.changePos(0.0f, 0.3f * Px::deltaTime);
	else if (Px::Keys[GLFW_KEY_S])
		px.changePos(0.0f, -0.3f * Px::deltaTime);

	if (Px::Keys[GLFW_KEY_A])
		px.changePos(-0.3f * Px::deltaTime, 0.0f);
	else if (Px::Keys[GLFW_KEY_D])
		px.changePos(0.3f * Px::deltaTime, 0.0f);
}

int main()
{
	objectsSetting();

	float colorChangeValue = 0.01f;
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		bg.changeBackground(glm::make_mat4x3(BgColor));
		for (int i = 0; i < 12; i += 1)
		{
			if (BgColor[i] >= 0.9f || BgColor[i] <= -0.0f)
				colorChangeValue = -colorChangeValue;
			BgColor[i] += colorChangeValue;
		}

		objectsEvents();
		manager.drawAll();
		manager.updateAll();
		window.swapBuffers();
		window.poolEvents();

	}
	return 0;
}