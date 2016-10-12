#include<GLFW\glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>    // std::chrono::seconds
#include "math.h"
#include<vector>

using namespace std;

const int width = 640;
const int height = 480;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	
	if (i0 == i1)
	{
		for (int y = j0; y < j1; y++)
		{
			drawPixel(i0, y, red, green, blue);
		}
	}

	else for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawOnPixelBuffer()
{
	//std::memset(pixels, 1.0f, sizeof(float)*width*height * 3); // doesn't work
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background

													//for (int i = 0; i<width*height; i++) {
													//	pixels[i * 3 + 0] = 1.0f; // red 
													//	pixels[i * 3 + 1] = 1.0f; // green
													//	pixels[i * 3 + 2] = 1.0f; // blue
											
}

class Box
{
	int x_c=100, y_c=100, r=50;
public:
	void draw()
	{
		drawLine(x_c - r, y_c + r, x_c + r, y_c + r, 0, 0, 1);
		drawLine(x_c - r, y_c - r, x_c + r, y_c - r, 0, 0, 1);
		drawLine(x_c - r, y_c - r, x_c - r, y_c + r, 0, 0, 1);
		drawLine(x_c + r, y_c - r, x_c + r, y_c + r, 0, 0, 1);
	}
};

class Circle
{
	int x_c=200, y_c=200, r_c=50;
public:
	void draw()
	{
		int x = r_c;
		int y = 0;
		int err = 0;
		
		while (x >= y)
		{
		drawPixel(x_c + x, y_c + y,0,0,1);
		drawPixel(x_c + y, y_c + x,0,0,1);
		drawPixel(x_c - y, y_c + x, 0, 0, 1);
		drawPixel(x_c - x, y_c + y, 0, 0, 1);
		drawPixel(x_c - x, y_c - y, 0, 0, 1);
		drawPixel(x_c - y, y_c - x, 0, 0, 1);
		drawPixel(x_c + y, y_c - x, 0, 0, 1);
		drawPixel(x_c + x, y_c - y, 0, 0, 1);
		y += 1;
		err += 1 + 2 * y;
		if (2 * (err - x) + 1 > 0)
		{
		x -= 1;
		err += 1 - 2 * x;
		}
		}
	}
};

class Geometric
{
public:
	virtual void draw() = 0;
};

template<class T_TYPE>
class Geo :public Geometric
{
public:
	void draw() {
		T_TYPE geo;
		geo.draw();
	}
};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

							  /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		drawOnPixelBuffer();
		//draw
		vector<Geometric*> obj;
		obj.push_back(new Geo<Circle>);
		obj.push_back(new Geo<Box>);
		
		for (auto itr : obj)
			itr->draw();
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		glfwSwapBuffers(window);

		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}