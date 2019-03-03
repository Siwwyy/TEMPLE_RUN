#include "../HEADERS/Keyboard_Input.h"

using namespace std;
using namespace KEY_PRESS_EVENTS;	//cause the class is in the own namespace named as KEY_PRESS_EVENTS

//initialization of static class members, space below
std::queue<int> Keyboard_Input::Key_Queue;
////////////////////////////////////////////////////////////

Keyboard_Input::Keyboard_Input():
	KeyState(0)
{
	Key_Queue.push(KeyState);
}

Keyboard_Input::Keyboard_Input(const int Key_Value):
	KeyState(Key_Value)
{
	//Key_Queue.push(KeyState);
	//std::cout << Key_Value << std::endl;
}

void KEY_PRESS_EVENTS::Keyboard_Input::updateInput_Key(GLFWwindow * window, glm::vec3 & position, glm::vec3 & rotation, glm::vec3 & scale)
{
	//std::cout << Key_Queue.back() << "HEHE" << endl;
	//system("pause");
	if (Key_Queue.back() == GLFW_KEY_W) //move forward
	{
		//Key_Queue.push(GLFW_KEY_W);
		position.z -= 0.01f;
		//Key_Queue.pop();
		//Key_Queue.back() = 0;
	}
	else if (Key_Queue.back() == GLFW_KEY_S) //move back
	{
	//	Key_Queue.push(GLFW_KEY_S);
		position.z += 0.01f;
		//Key_Queue.back() = 0;
	}
	else if (Key_Queue.back() == GLFW_KEY_A) //go left
	{
		//Key_Queue.push(GLFW_KEY_A);
		position.x -= 0.01f;
		//Key_Queue.back() = 0;
	}
	else if (Key_Queue.back() == GLFW_KEY_D) //go right
	{
		//Key_Queue.push(GLFW_KEY_D);
		position.x += 0.01f;
		//Key_Queue.back() = 0;
	}
	else if (Key_Queue.back() == GLFW_KEY_Q) //rotate left
	{
		//Key_Queue.push(GLFW_KEY_Q);
		rotation.y -= 1.f;
	}
	else if (Key_Queue.back() == GLFW_KEY_E) //rotate right
	{
		//Key_Queue.push(GLFW_KEY_E);
		rotation.y += 1.f;
	}
	else if (Key_Queue.back() == GLFW_KEY_ESCAPE) //close the window
	{
		//Key_Queue.push(GLFW_KEY_ESCAPE);
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if (Key_Queue.back() == GLFW_KEY_Z) //scale ++
	{
		//Key_Queue.push(GLFW_KEY_Z);
		scale += 0.1f;
	}
	else if (Key_Queue.back() == GLFW_KEY_X) //scale --
	{
		//Key_Queue.push(GLFW_KEY_X);
		scale -= 0.1f;
	}
	Key_Queue.back() = 0;
}

void KEY_PRESS_EVENTS::Keyboard_Input::SetKeyState(const int KeyState)
{
	std::cout << KeyState << endl;
	//this->KeyState = KeyState;
	//Key_Queue.push(this->KeyState);
	Key_Queue.push(KeyState);
}

Keyboard_Input::~Keyboard_Input()
{
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) //move forward
	//{
	//	Key_Queue.push(GLFW_KEY_W);
	//	position.z -= 0.001f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) //move back
	//{
	//	Key_Queue.push(GLFW_KEY_S);
	//	position.z += 0.001f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) //go left
	//{
	//	Key_Queue.push(GLFW_KEY_A);
	//	position.x -= 0.001f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) //go right
	//{
	//	Key_Queue.push(GLFW_KEY_D);
	//	position.x += 0.001f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) //rotate left
	//{
	//	Key_Queue.push(GLFW_KEY_Q);
	//	rotation.y -= 1.f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) //rotate right
	//{
	//	Key_Queue.push(GLFW_KEY_E);
	//	rotation.y += 1.f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //close the window
	//{
	//	Key_Queue.push(GLFW_KEY_ESCAPE);
	//	glfwSetWindowShouldClose(window, GLFW_TRUE);
	//}
	//else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) //scale ++
	//{
	//	Key_Queue.push(GLFW_KEY_Z);
	//	scale += 0.1f;
	//}
	//else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) //scale --
	//{
	//	Key_Queue.push(GLFW_KEY_X);
	//	scale -= 0.1f;
	//}
	//Key_Queue.pop();
}