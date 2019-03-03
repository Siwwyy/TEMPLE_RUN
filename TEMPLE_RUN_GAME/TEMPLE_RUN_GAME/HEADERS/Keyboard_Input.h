// _KEYBOARD_INPUT_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
*/
#ifndef _KEYBOARD_INPUT_H_
#define _KEYBOARD_INPUT_H_
#pragma once

/*
	SPACE FOR INCLUDING
*/
//GLEW
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm.hpp>
#include <vec2.hpp>
#include <vec3.hpp>
#include <vec4.hpp>
#include <mat4x4.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

//SOIL2
#include<SOIL2.h>

#include <queue>
//////////////////////////////////////////////

namespace KEY_PRESS_EVENTS
{
	class Keyboard_Input
	{
	private:
		/*
			VARIABLES PRIVATE
		*/
		std::queue<int> Key_Queue;
		//////////////////////////////////////////////////////////////////////////////
	protected:
		/*
			VARIABLES PROTECTED
		*/

		//////////////////////////////////////////////////////////////////////////////
	private:
		/*
			KONSTRUKTORY
		*/
		explicit Keyboard_Input();
		explicit Keyboard_Input(const int Key_Value);
		Keyboard_Input(const Keyboard_Input & Object) = delete;
		//////////////////////////////////////////////////////////////////////////////
		/*
			FUNKCJE PUBLIC
		*/
		void updateInput_Key(GLFWwindow * window, glm::vec3 & position, glm::vec3 & rotation, glm::vec3 & scale);
		//////////////////////////////////////////////////////////////////////////////
		/*
			SETTERY
		*/

		//////////////////////////////////////////////////////////////////////////////
		/*
			GETTERY
		*/

		//////////////////////////////////////////////////////////////////////////////
		/*
			OPERATORY
		*/
		//Jednoargumentowe
		Keyboard_Input & operator=(const Keyboard_Input & Object) = delete;
		//Dwuargumentowe
		//////////////////////////////////////////////////////////////////////////////
		/*
			DESTRUKTOR
		*/
		virtual ~Keyboard_Input();
	};
}

#endif /* _KEYBOARD_INPUT_H_ */