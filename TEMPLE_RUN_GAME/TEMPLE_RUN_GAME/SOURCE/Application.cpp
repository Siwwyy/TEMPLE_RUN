//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//// GLM
//#include "vendor/glm/glm.hpp"
//#include "vendor/glm/gtc/matrix_transform.hpp"
//#include "vendor/glm/gtc/type_ptr.hpp"
//
//#include <iostream>
//
//// Cherno
//#include "Renderer.h"
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "IndexBuffer.h"
//#include "VertexArray.h"
//#include "Shader.h"
//#include "Texture.h"
//// Mine
//#include "Keyboard.h"

#include "../HEADERS/libs.h"

void processInput(GLFWwindow *window, glm::mat4& view, glm::mat4& proj, glm::mat4 &mvp, Shader& shader, int &x, int &y, Keyboard& kb) // test
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	KeyStates newKeyStates;

	newKeyStates.W = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ? true : false);
	newKeyStates.A = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ? true : false);
	newKeyStates.S = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ? true : false);
	newKeyStates.D = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ? true : false);

	kb.Update(newKeyStates);

	x += kb.getDirX();
	y += kb.getDirY();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0));
	mvp = proj * view * model;
	shader.SetUniformMat4f("u_MVP", mvp);

	std::cout << "Keys pressed: ";
	//std::cout << ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) ? "W " : "  ");
	//std::cout << ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) ? "A " : "  ");
	//std::cout << ((glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) ? "S " : "  ");
	//std::cout << ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) ? "D \n" : "  \n");

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
	window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// test
	//glfwSwapInterval(1);
	glfwSwapInterval(1.5);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error!\n";
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{

		// Specify coordinates for rectangle
		float positions[] = {
		   100.0f, 100.0f, 0.0f, 0.0f, // 0
	   	   340.0f, 100.0f, 1.0f, 0.0f, // 1
		   340.0f, 280.0f, 1.0f, 1.0f, // 2
		   100.0f, 280.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		// Texture blending
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		// Set up vertex buffer & vertex array
		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		// Set up index buffer
		IndexBuffer ib(indices, 6);

		// Projection matrix
		//glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

		glm::mat4 mvp = proj * view * model;

		// Create shaders
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		// Textures
		Texture texture("res/textures/kot.png");
		shader.SetUniform1i("u_Texture", 0);
		texture.Bind();

		Renderer renderer;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // test

		// Cat position & keryboard functionality
		int x = 200;
		int y = 200;
		Keyboard kb;

		float r = 0.0f; // test
		float increment = 0.05f; // test
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			processInput(window, view, proj, mvp, shader, x, y, kb); // test
			/* Render here */
			renderer.Clear();

			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			//glClearColor(r/2 + 0.1, r/3 + (3*r)-1, r/3+0.4, 1.0f); // lmao

			renderer.Draw(va, ib, shader);

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
		vb.Unbind();
		ib.Unbind();

	}

	glfwTerminate();
	return 0;
}