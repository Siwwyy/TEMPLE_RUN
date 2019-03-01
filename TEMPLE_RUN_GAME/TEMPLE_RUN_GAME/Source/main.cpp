#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
	{
		return -1;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	//if (glewInit() != GLEW_OK)
	//{
	//	std::cout << "ERROR WITH GLEW INIT" << std::endl;
	//}

	std::cout << glGetString(GL_VERSION) << std::endl;

	unsigned int a = 0;
	//glGenBuffers(1, &a);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/*glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();*/

		glBegin(GL_POLYGON);
		glVertex2f(0.5f, 0.5f);			//I
		glVertex2f(-0.5f, 0.5f);		//II
		glVertex2f(-0.5f, -0.5f);		//III
		glVertex2f(0.5f, -0.5f);		//IV
		glEnd();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}