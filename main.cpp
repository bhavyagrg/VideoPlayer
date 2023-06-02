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
	for (int y = 25;y<75; ++y)
	{
		for (int x = 25;x<75; ++x)
		{
			data[y * 100 * 3 + x * 3] = 0x00;//Red:0
			data[y * 100 * 3 + x * 3 + 1] = 0x00;//Green : 0
			data[y * 100 * 3 + x * 3 + 2] = 0xff;//Blue:255 
		}

	}

	glfwMakeContextCurrent(window);

	//Creating Texture
	GLuint tex_handle;
	int tex_width = 100;
	int tex_height = 100; 
	glGenTextures(1, &tex_handle);
	glBindTexture(GL_TEXTURE_2D, tex_handle);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width,tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		//Set up Orphographic Projection
		int window_width, window_height;
		glfwGetFramebufferSize(window, &window_width, &window_height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, window_width, window_height, 0, -1, 1); // -1,1 are for z axis and we don't care about them right now,but basic values are -1,1
		glMatrixMode(GL_MODELVIEW);

		glViewport(0, 0, window_width, window_height);
		
		//Render Texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex2i(200, 200); 
		glTexCoord2d(1, 0); glVertex2i(200 + tex_width * 2, 200);
		glTexCoord2d(1, 1); glVertex2i(200 + tex_width * 2, 200 + tex_height * 2);
		glTexCoord2d(0, 1); glVertex2i(200,200 + tex_height * 2);
		glEnd();
		glDisable(GL_TEXTURE_2D);

		//glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();
	}

	  


	return 0;
}
