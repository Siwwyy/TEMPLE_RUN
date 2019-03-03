#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void processInput(GLFWwindow *window) // test
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// test
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!\n";
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{

	// Specify coordinates for rectangle
	float positions[] = {
	   -0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
	   -0.5f,  0.5f,
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Set up vertex buffer & vertex array
	VertexArray va;
 	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	// Set up index buffer
	IndexBuffer ib(indices, 6);
	//va.Bind(); // renderer.draw()
	//ib.Bind(); // renderer.draw()

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

	// Create shaders
	Shader shader("res/shaders/Basic.shader");
	//shader.Bind(); // renderer.draw()
	//ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	//unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	//GLCall(glUseProgram(shader));

	//shader.Bind();
	//shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	//GLCall(int location = glGetUniformLocation(shader, "u_Color"));
	//GLCall(glUniform4f(location, 0.1f, 0.3f, 0.8f, 1.0f));
	//ASSERT(location != -1);

	Renderer renderer;


	float r = 0.0f; // test
	float increment = 0.05f; // test
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window); // test
		/* Render here */
		renderer.Clear();
		//GLCall(glClear(GL_COLOR_BUFFER_BIT));

		shader.Bind();
		shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
		//GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		renderer.Draw(va, ib, shader);
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		// test - uniforms
		if (r > 1.0f) {
			increment = -0.05f;
		}
		else if (r < 0.0f) {
			increment = 0.05f;
		}

		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	va.Unbind();
	shader.Unbind();
	//GLCall(glUseProgram(0));
	vb.Unbind();
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ib.Unbind();
	//GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	//GLCall(glDeleteProgram(shader));
	
	}

	glfwTerminate();
	return 0;
}