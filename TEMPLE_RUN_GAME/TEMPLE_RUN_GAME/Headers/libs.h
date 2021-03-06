#ifndef _LIBS_H_
#define _LIBS_H_
#pragma once

/*
	OPENGL AND CONNECTED LIBRARIES
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

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

/*
	BASIC LIBRARIES
*/
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <fstream>

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//INCLUDING OWN HEADER
#include "../HEADERS/Keyboard_Input.h"
//#include "../HEADERS/Shader.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
	STRUCTURES
*/

//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec3 color;
//	glm::vec2 texcoord;
//	glm::vec3 normal;
//};

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//Externs
//extern KEY_PRESS_EVENTS::Keyboard_Input Object_KeyBoard;
//static KEY_PRESS_EVENTS::Keyboard_Input Object_KeyBoard;
#endif /* _LIBS_H_ */