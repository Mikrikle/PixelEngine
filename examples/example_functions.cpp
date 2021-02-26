/*

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <iostream>

#include "../shaders/shader.h"
#include "../includes/glm/glm.hpp"
#include "../includes/glm/gtc/matrix_transform.hpp"
#include "../includes/glm/gtc/type_ptr.hpp"

#include "../includes/windowGLFM.h"
#include "../includes/PixelEngine.h"

int SIZEX = 800;
int SIZEY = SIZEX;
double scale = 30.0;
double step = 0.005;


double f(double x)
{
	return cos(sin(x) * x) * tan(x);
}

void render(Px::PxCanvas &px)
{
	for (int i = SIZEX/2, j= SIZEX / 2; i < SIZEX; i += scale, j-= scale)
	{
		px.setLine(0, i, 0.1f, 0.1f, 0.1f, SIZEY - 1, i, 1);
		px.setLine(0, j, 0.1f, 0.1f, 0.1f, SIZEY - 1, j, 1);
	}
	for (int i = SIZEY/2, j = SIZEX / 2; i < SIZEY; i += scale, j-=scale)
	{
		px.setLine(i, 0, 0.1f, 0.1f, 0.1f, i, SIZEX - 1, 1);
		px.setLine(j, 0, 0.1f, 0.1f, 0.1f, j, SIZEX - 1, 1);
	}
	px.setLine(SIZEY / 2, 0, 0.5f, 0.5f, 0.5f, SIZEY / 2, SIZEX - 1, 1);
	px.setLine(0, SIZEX / 2, 0.5f, 0.5f, 0.5f, SIZEY - 1, SIZEX / 2, 1);

	for (double x = -SIZEX / 2.0 + 1; x < SIZEX / 2.0 - 1; x += step)
	{
		if (!isnan(f(x)))
		{
			px.setPixel(SIZEY - round(f(x / scale) * scale + SIZEY / 2.0), round(x + SIZEX / 2.0), 1.0f, 0.0f, 0.0f);
		}
	}
}

void event_px_scroll(Px::PxCanvas& self)
{
	if ((self.getScale() > 1.0f && Px::ScrollY < 0) || (self.getScale() <= 10.0f && Px::ScrollY > 0))
		self.increaseScale(Px::ScrollY / 2.0f);
	if (self.getScale() < 1.0f)
		self.setScale(1.0f);
	if (self.getScale() > 10.0f)
		self.setScale(10.0f);
	Px::ScrollY = 0;
}

void event_px_move(Px::PxCanvas& self, float deltaTime)
{
	if (Px::Keys[GLFW_KEY_SPACE])
	{
		self.clear();
		scale = 30.0;
		self.setScale(1.0f);
		render(self);
	}
	if (Px::Keys[GLFW_KEY_UP])
	{
		if (scale < 100)
			scale += 1;
		self.clear();
		render(self);
	}
	if (Px::Keys[GLFW_KEY_DOWN])
	{
		if (scale > 6)
			scale -= 1;
		self.clear();
		render(self);
	}
}


int main()
{
	Px::WindowSizeX = 800;
	Px::WindowSizeY = 800;
	Window window(Px::WindowSizeX, Px::WindowSizeY, "Functions");
	Shader shader("../shaders/vertexShader.txt", "../shaders/fragmentShader.txt");
	float colors[12]{ 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f };
	Px::PxCanvas px(SIZEX, SIZEY, 1.0f, 1.0f, glm::make_mat4x3(colors), &shader, 1.0f, 0.0f, 0.0f, nullptr, event_px_scroll, event_px_move);
	px.setMoveSpeed(0.1f);

	render(px);

	while (!window.isShouldClose())
	{
		window.clearWindow(0.0f, 0.0f, 0.0f);

		px.setOpacity(0.2f);
		px.draw();
		px.eventProcessing(1.0f);

		window.swapBuffers();
		window.poolEvents();
	}
	return 0;

}

*/
