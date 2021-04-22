#include <iostream>
#include <math.h>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

double f(double x)
{
	return cos(sin(x) * x) * tan(x);
}

int SIZEX = 800;
int SIZEY = SIZEX;
double scale = 30.0;
double step = 0.005;
int px::windowWidth = 800;
int px::windowHeight = 800;
Window window(px::windowWidth, px::windowHeight, "Functions");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader *px::DefaultShader = &sh;

px::PxCanvas px_canvas(SIZEX, SIZEY);

void render()
{
	for (int i = SIZEX / 2, j = SIZEX / 2; i < SIZEX; i += scale, j -= scale)
	{
		px_canvas.drawLine(0, i, 0.1f, 0.1f, 0.1f, SIZEY - 1, i, 1);
		px_canvas.drawLine(0, j, 0.1f, 0.1f, 0.1f, SIZEY - 1, j, 1);
	}
	for (int i = SIZEY / 2, j = SIZEX / 2; i < SIZEY; i += scale, j -= scale)
	{
		px_canvas.drawLine(i, 0, 0.1f, 0.1f, 0.1f, i, SIZEX - 1, 1);
		px_canvas.drawLine(j, 0, 0.1f, 0.1f, 0.1f, j, SIZEX - 1, 1);
	}
	px_canvas.drawLine(SIZEY / 2, 0, 0.5f, 0.5f, 0.5f, SIZEY / 2, SIZEX - 1, 1);
	px_canvas.drawLine(0, SIZEX / 2, 0.5f, 0.5f, 0.5f, SIZEY - 1, SIZEX / 2, 1);

	for (double x = -SIZEX / 2.0 + 1; x < SIZEX / 2.0 - 1; x += step)
	{
		if (!isnan(f(x)))
		{
			px_canvas.setPixel(round(x + SIZEX / 2.0), SIZEY - round(f(x / scale) * scale + SIZEY / 2.0), 1.0f, 0.0f, 0.0f);
		}
	}
}

void objectsEvents()
{
	if (px::keyboardKeys[GLFW_KEY_UP])
	{
		if (scale < 100)
			scale += 1;
		px_canvas.fillBlack();
		render();
	}
	if (px::keyboardKeys[GLFW_KEY_DOWN])
	{
		if (scale > 6)
			scale -= 1;
		px_canvas.fillBlack();
		render();
	}
}

int main()
{
	px_canvas.setTextureOpacity(0.8f);
	px_canvas.setUnderTextureColor(glm::mat4x3(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f));
	render();

	while (!window.isShouldClose())
	{
		window.clearWindow(0.0f, 0.0f, 0.0f);

		px_canvas.draw();
		px_canvas.update();
		objectsEvents();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}