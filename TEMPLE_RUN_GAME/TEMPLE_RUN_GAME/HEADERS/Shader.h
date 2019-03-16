// _SHADER_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
*/

#ifndef _SHADER_H_
#define _SHADER_H_
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

class Shader
{
private:
	/*
		VARIABLES PRIVATE
	*/
	GLuint id;

	
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PRIVATE
	*/
	std::string loadShaderSource(const char* filename);
	GLuint loadShader(GLenum type, const char* filename);
	void linkProgram(GLuint vertexShader, GLuint geometryShader, GLuint fragmentShader);
	//////////////////////////////////////////////////////////////////////////////
protected:

public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void use();
	void unuse();
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	void setVec1f(GLfloat value, const GLchar* name);
	void set1i(GLint value, const GLchar* name);
	void setVec2f(glm::fvec2 value, const GLchar* name);
	void setVec3f(glm::fvec3 value, const GLchar* name);
	void setVec4f(glm::fvec4 value, const GLchar* name);
	void setMat3fv(glm::mat3 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	void setMat4fv(glm::mat4 value, const GLchar* name, GLboolean transpose = GL_FALSE);
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/

	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	~Shader();
	//////////////////////////////////////////////////////////////////////////////
};

#endif /* _SHADER_H_ */