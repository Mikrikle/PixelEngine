# PixelEngine

Engine for drawing pixel-based 2D graphics to the full window. Based on OpenGL 3.3+ and GLFW.

Designed for cellular automata, drawing, and simple games.

![image](https://user-images.githubusercontent.com/50238538/107142282-cc375800-693e-11eb-9116-cc84fc0111e9.png)

### How to use

* install cmake https://cmake.org/download/
* git clone "https://github.com/Miriskrit/PixelEngine.git"
* Use cmake to build project to "path to the project"/build
* * cd PixelEngine
* * mkdir build
* * cd build
* * cmake ..
* * cmake --build .
* Run programm
* * cd Debug
* * ./PixelEngine.exe
* * (If the window does not open, run the file as an administrator)

You should see this window

![image](https://user-images.githubusercontent.com/50238538/116972733-22106780-acc4-11eb-8208-eac39ac606d3.png)



### base code example
``` cpp
#include <iostream>
#include "./shaders/shader.h"
#include "./includes/PixelEngine.h"
int px::windowWidth = 800;
int px::windowHeight = 800;
Window window(px::windowWidth, px::windowHeight, "App_name");
Shader sh("../../src/shaders/vertexShader.txt", "../../src/shaders/fragmentShader.txt");
Shader* px::DefaultShader = &sh;

class App : public px::PxBaseApp
{
public:
	App()
	{
		manager.init({ &rectangle });
		grid.init(1, 1, { {&rectangle} });
		init();
	}

	void objectsEvents()
	{
	}

	void objectsSetting()
	{
		rectangle.setUnderTextureColor(glm::mat2x3(0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f));
	}

private:
	px::PxRectangle rectangle;
};

int main()
{
	App TestApp;
	window.enable_blend();
	while (!window.isShouldClose())
	{
		window.clearWindow(0.1f, 0.1f, 0.1f);
		TestApp.run();
		window.swapBuffers();
		window.poolEvents();
	}
	return 0;
}
```
