// _TEXTURE_H_ standard header
/*
 *			   Copyright (c) by Damian Andrysiak. All rights reserved.
*/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_
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

class Texture
{
private:
	/*
		VARIABLES PRIVATE
	*/
	GLuint id;
	int width;
	int height;
	unsigned int type;
	GLint textureUnit;
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	
	//////////////////////////////////////////////////////////////////////////////
protected:

public:
	/*
		KONSTRUKTORY PUBLIC
	*/
	Texture(const char* fileName, GLenum type, GLint texture_unit);
//	Texture(const char* vertexFile, const char* fragmentFile, const char* geometryFile = "");
	//////////////////////////////////////////////////////////////////////////////
	/*
		FUNKCJE PUBLIC
	*/
	void bind();
	void unbind();
	void loadfromfile(const char* fileName);
	//////////////////////////////////////////////////////////////////////////////
	/*
		SETTERY PUBLIC
	*/
	
	//////////////////////////////////////////////////////////////////////////////
	/*
		GETTERY PUBLIC
	*/
	__forceinline GLuint getID() const;
	GLuint get_texture_unit() const;
	//////////////////////////////////////////////////////////////////////////////
	/*
		DESTRUKTOR
	*/
	~Texture();
	//////////////////////////////////////////////////////////////////////////////
};

#endif /* _TEXTURE_H_ */