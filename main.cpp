#include<iostream>
#include<GLFW/glfw3.h>

int main(int argc, const char** argv)
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		std::cout<<"Couldn't init GLFW\n"<<std::endl;
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello World",NULL,NULL);
	if (!window) 
	{
		std::cout << "Couldn't Open Window" << std::endl;
		return -1;
	}

	unsigned char* data = new unsigned char[100 * 100 * 3];
	for (int y = 0; y < 100; ++y) 
	{
		for (int x = 0; x < 100; ++x)
		{
			data[y * 100 * 3 + x * 3] = 0xff;//Red : 255
			data[y * 100 * 3 + x * 3 + 1] = 0x00;//Green : 0
			data[y * 100 * 3 + x * 3 + 2] = 0x00;//Blue : 0
		}

	}

	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();
	}




	return 0;
}
