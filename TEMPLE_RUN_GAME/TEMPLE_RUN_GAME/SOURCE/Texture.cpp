#include "../HEADERS/Texture.h"

using namespace std;

Texture::Texture(const char* fileName, GLenum type, GLint texture_unit)
{
	//unsigned char* image = SOIL_load_image("IMAGES/mesh.png", &this->width, &this->height, nullptr, SOIL_LOAD_RGB);
	/*if (this->id)	//remember
	{
		glDeleteTextures(1, &this->id);
	}*/
	this->type = type;
	this->textureUnit = texture_unit;
	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, nullptr, SOIL_LOAD_RGB);
	//unsigned char* image = SOIL_load_image("IMAGES/sunset.png", &image_width, &image_height, NULL, SOIL_LOAD_RGB);

	GLuint texture; //0 means ID oh the image
	glGenTextures(1, &this->id);
	glBindTexture(type, this->id);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//magnify pixels 
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					//minimalize pixels

	if (image)
	{
		std::cerr << "TEXTURE_LOADED" << '\n';
		/*	std::cerr << image << '\n';
			std::cerr << image_width << '\n';
			std::cerr << image_height << '\n';*/
		assert(image != NULL);
		assert(width != NULL);
		assert(height != NULL);
		glTexImage2D(type, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//char is also a byte
		glGenerateMipmap(type);
		glDisable(GL_CULL_FACE);
	}
	else
	{
		std::cerr << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << fileName << '\n';
	}

	glActiveTexture(0);
	glBindTexture(type, 0);	//0 means 0 no active binde texture, 0 texture in there
	SOIL_free_image_data(image);
}

void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0 + this->textureUnit);
	glBindTexture(this->type, this->id);
}

void Texture::unbind()
{
	glActiveTexture(0);
	glBindTexture(this->type, 0);
}

void Texture::loadfromfile(const char * fileName)
{
	//unsigned char* image = SOIL_load_image("IMAGES/mesh.png", &this->width, &this->height, nullptr, SOIL_LOAD_RGB);
	if (this->id)	//remember
	{
		glDeleteTextures(1, &this->id);
	}
	unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, nullptr, SOIL_LOAD_RGB);
	//unsigned char* image = SOIL_load_image("IMAGES/sunset.png", &image_width, &image_height, NULL, SOIL_LOAD_RGB);

	GLuint texture; //0 means ID oh the image
	glGenTextures(1, &this->id);
	glBindTexture(this->type, this->id);

	glTexParameteri(this->type, GL_TEXTURE_WRAP_S, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(this->type, GL_TEXTURE_WRAP_T, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//magnify pixels 
	glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					//minimalize pixels

	if (image)
	{
		std::cerr << "TEXTURE_LOADED" << '\n';
		/*	std::cerr << image << '\n';
			std::cerr << image_width << '\n';
			std::cerr << image_height << '\n';*/
		assert(image != NULL);
		assert(width != NULL);
		assert(height != NULL);
		glTexImage2D(this->type, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//char is also a byte
		glGenerateMipmap(this->type);
		glDisable(GL_CULL_FACE);
	}
	else
	{
		std::cerr << "ERROR::TEXTURE::TEXTURE_LOADING_FAILED" << fileName << '\n';
	}

	glActiveTexture(0);
	glBindTexture(this->type, 0);	//0 means 0 no active binde texture, 0 texture in there
	SOIL_free_image_data(image);
}

__forceinline GLuint Texture::getID() const
{
	return this->id;
}

GLuint Texture::get_texture_unit() const
{
	return this->textureUnit;
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->id);
}