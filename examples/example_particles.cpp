#include <iostream>
#include <fstream>
#include <deque>
#include <array>
#include <ctime>
#include <algorithm>

#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"

int px::windowWidth = 800;
int px::windowHeight = 800;

Window window(px::windowWidth, px::windowHeight, "Game");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

px::PxCanvas cvs(px::windowHeight, px::windowWidth);
px::GridLayout test_grl(1, 1, { {&cvs} });
px::ManagerObjects manager{ &cvs };

const double G = 6.674;
const int MassCenterR = 15;

class Particle
{
public:
	Particle()
	{
		pos = glm::vec2(rand() % (px::windowWidth)-px::windowWidth / 2, rand() % (px::windowHeight)-px::windowHeight / 2);
		color = glm::vec3(static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX, static_cast<double>(rand()) / RAND_MAX);
		m = 1;
		speed = glm::vec2(0.0, 0.0);
	}

	void move()
	{
		pos += speed;
	}

	glm::vec2 pos;
	glm::vec3 color;
	glm::vec2 speed;
	double m;
};

class MassCenter
{
public:
	MassCenter()
	{
		pos = glm::vec2(0, 0);
		m = 100000;
	}

	glm::vec2 pos;
	double m;
};

std::array<Particle, 10'000> particles;
std::array<MassCenter, 2> mCenters;

int getSign(int value)
{
	if (value < 0)
		return -1;
	else
		return 1;
}

void particles_update()
{
	std::for_each(std::begin(particles), std::end(particles),
		[](Particle& p)
	{
		std::for_each(std::begin(mCenters), std::end(mCenters),
			[&p](MassCenter& mc)
		{
			glm::vec2 move(mc.pos.x - p.pos.x, mc.pos.y - p.pos.y);
			double r = glm::length(move);
			if (r != 0)
			{
				if (r < MassCenterR && r > 0)
				{
					r = MassCenterR;
				}
				else if (r > -MassCenterR && r < 0)
				{
					r = -MassCenterR;
				}
				if (r > (px::windowHeight + px::windowWidth) / 2)
				{
					r /= 10;
				}
				double a_p = G * p.m / (r * r);
				p.speed = glm::vec2(p.speed.x + (a_p * getSign(move.x)), p.speed.y + (a_p * getSign(move.y)));
			}
		}
		);
		if (p.pos.x + p.speed.x < px::windowWidth / 2 && p.pos.x + p.speed.x > -px::windowWidth / 2 &&
			p.pos.y + p.speed.y < px::windowHeight / 2 && p.pos.y + p.speed.y > -px::windowHeight / 2)
		{
			p.move();
		}
		else
		{
			p.speed = glm::vec2(0.0f);
		}
	}
	);
}

void draw_particles()
{
	cvs.fillBlack();
	std::for_each(std::begin(particles), std::end(particles),
		[](Particle& p)
	{
		cvs.setPixel(static_cast<int>(p.pos.x + px::windowWidth / 2.0f), static_cast<int>(p.pos.y + px::windowHeight / 2.0f), p.color);
	}
	);

	std::for_each(std::begin(mCenters), std::end(mCenters),
		[](MassCenter& mc)
	{
		cvs.drawCircle(static_cast<int>(mc.pos.x + px::windowWidth / 2.0f), static_cast<int>(mc.pos.y + px::windowHeight / 2.0f), 1.0f, 1.0f, 1.0f, MassCenterR, false);
	}
	);
}

void objectsSetting()
{
	cvs.setUnderTextureColor(0.58f, 0.78f, 0.89f);
	cvs.setTextureOpacity(0.85f);
}

void objectsEvents()
{
	if (px::isMouseLeftClick)
	{
		mCenters[1].pos = glm::vec2(cvs.getMouseCol() - px::windowWidth / 2, cvs.getMouseRow() - px::windowHeight / 2);
	}
	else
	{
		mCenters[1].pos = glm::vec2(0.0f, 0.0f);
	}
}

int main()
{
	srand(time(0));
	objectsSetting();
	float colorChangeValue = 0.01f;

	window.enable_blend();
	while (!window.isShouldClose())
	{
		window.clearWindow(0.2f, 0.3f, 0.3f);

		particles_update();
		draw_particles();

		manager.updateAll();
		objectsEvents();
		manager.drawAll();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}