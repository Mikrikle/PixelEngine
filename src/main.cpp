#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"


Px::EventsDefaultManager pxmanager;

void btn_click(Px::PxCanvas& obj)
{
	obj.clear();
}

void event_px_on_click(Px::PxCanvas& self)
{
	if(Px::MouseLeftClick)
		self.setPixel(1.0f, 0.0f, 0.0f);
	if (Px::MouseRightClick)
		self.setPixel(0.0f, 0.0f, 0.0f);
}

void event_px_scroll(Px::PxCanvas& self)
{
	if ((self.getScale() > 0.1f && Px::ScrollY < 0) || (self.getScale() <= 1.0f && Px::ScrollY > 0))
		self.increaseScale(Px::ScrollY / 4.0f);
	if (self.getScale() < 0.1f)
		self.setScale(0.1f);
	if (self.getScale() > 1.0f)
		self.setScale(1.0f);
	Px::ScrollY = 0;
}

void event_px_move(Px::PxCanvas& self, float deltaTime)
{
	if (Px::Keys[GLFW_KEY_A])
		self.increaseTranslate(-0.1f * deltaTime * self.getMoveSpeed(), 0.0f);
	if (Px::Keys[GLFW_KEY_D])
		self.increaseTranslate(0.1f * deltaTime * self.getMoveSpeed(), 0.0f);
	if (Px::Keys[GLFW_KEY_S])
		self.increaseTranslate(0.0f, -0.1f * deltaTime * self.getMoveSpeed());
	if (Px::Keys[GLFW_KEY_W])
		self.increaseTranslate(0.0f, 0.1f * deltaTime * self.getMoveSpeed());
}

int main()
{
	Px::WindowSizeX = 800;
	Px::WindowSizeY = 800;
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Game");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");


	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Px::PxCanvas px(100, 200, 0.75f, 0.5f, glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, -0.25f, event_px_on_click, event_px_scroll, event_px_move);
	px.setMoveSpeed(3.0f);

	float BgColor[12]{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f };
	float colorChangeValue = 0.01f;
	Px::PxStaticBackground bg(glm::make_mat4x3(BgColor), &shader);

	float BtnColor[6]{ 0.0f, 0.0f, 0.0f, 0.6f, 0.0f, 0.0f, };
	Px::PxButtonForObj<Px::PxCanvas> btn(0.05f, 0.05f, glm::make_mat2x3(BtnColor), &shader, 1.0f, 0.9f, 0.9f, btn_click, px);

	pxmanager.appendObj(px);
	pxmanager.appendObj(btn);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		bg.changeBackground(glm::make_mat4x3(BgColor));
		
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		for (int i = 0; i < 12; i += 1)
		{
			if (BgColor[i] >= 0.9f || BgColor[i] <= -0.0f)
				colorChangeValue = -colorChangeValue;
			BgColor[i] += colorChangeValue;
		}

		bg.draw();
		px.setOpacity(0.2f);
		px.draw();
		btn.draw();

		window.swapBuffers();
		window.poolEvents();
		pxmanager.updateEvents(deltaTime);
	}
	return 0;

}