#include "../HEADERS/libs.h"
#include "../HEADERS/Vertex.h"
#include "../HEADERS/Shader.h"
#include "../HEADERS/Texture.h"
#include "../HEADERS/Mesh.h"
#include "../HEADERS/Material.h"

//INCLUDING OWN HEADER
//#include "../HEADERS/Keyboard_Input.h"	//own header are including here

////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace KEY_PRESS_EVENTS;		//own namespace

KEY_PRESS_EVENTS::Keyboard_Input Object_KeyBoard; //usun

Vertex vertices[] =
{
	//Position	0 1 2							//Color	RGB									//Texcoords (texture coordinates)			//Normals
	//TRIANGLE ONE
	glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),						glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(-0.5f, -0.5, 0.f),				glm::vec3(0.f, 1.f, 0.f),					glm::vec2(0.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),
	glm::vec3(0.5f, -0.5f, 0.f),				glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),						glm::vec3(0.f, 0.f, 1.f),

	//TRIANGLE TWO
	/*glm::vec3(-0.5f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),					glm::vec2(0.f, 1.f),
	glm::vec3(0.5f, -0.5, 0.f),					glm::vec3(0.f, 0.f, 1.f),					glm::vec2(1.f, 0.f),*/
	glm::vec3(0.5f, 0.5f, 0.f),					glm::vec3(1.f, 1.f, 0.f),					glm::vec2(1.f, 1.f),						glm::vec3(0.f, 0.f, 1.f)
};
unsigned nrOfVertices = (sizeof(vertices) / sizeof(Vertex));

GLuint indices[] =
{
	0,1,2, //triangle one
	0,2,3 //triangle two
	//3,4,5 //triangle two, using 6 vertices
};
unsigned nrOfIndices = (sizeof(indices) / sizeof(GLuint));

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

void updateInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void framebuffer_resize_callback(GLFWwindow * window, int fbW, int fbH)
{
	glViewport(0, 0, fbW, fbH);
}

bool loadShaders(GLuint & program)
{
	bool load_success = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	//vertex
	in_file.open("vertex_core.glsl");

	if (in_file.is_open() == true)
	{
		while (std::getline(in_file, temp))
		{
			src += temp + '\n';
		}
	}
	else
	{
		std::cerr << "MAIN.CPP::PROBLEM:WITH:FILE:NOTOPEN::LOADESHADERS::VERTEX" << '\n';
		load_success = false;
	}

	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar * vertSrc = src.c_str();
	glShaderSource(vertexShader,1,&vertSrc,NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader,512,NULL, infoLog);
		std::cerr << "MAIN.CPP::PROBLEM:WITH:COMPILE:VERTEX:SHADERS" << '\n';
		std::cerr << infoLog << '\n';
		load_success = false;
	}

	temp = "";
	src = "";

	//Fragment
	in_file.open("fragment_core.glsl");

	if (in_file.is_open() == true)
	{
		while (std::getline(in_file, temp))
		{
			src += temp + '\n';
		}
	}
	else
	{
		std::cerr << "MAIN.CPP::PROBLEM:WITH:FILE:NOTOPEN::LOADESHADERS::FRAGMENT" << '\n';
		load_success = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar * fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "MAIN.CPP::PROBLEM:WITH:COMPILE:FRAGMENT:SHADERS" << '\n';
		std::cerr << infoLog << '\n';
		load_success = false;
	}

	temp = "";
	src = "";
	//Program
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cerr << "MAIN.CPP::PROBLEM:WITH:LOADSHADER:COUT_NOT_LINK_PROGRAM" << '\n';
		std::cerr << infoLog << '\n';
		load_success = false;
	}

	//End
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return load_success;
}

//bool KeyEvent(KEY_EVENT_RECORD & krec, HANDLE _HANDLE_PARAM)
//{
//	DWORD cc;
//	INPUT_RECORD IN_REC;
//
//	for (;;)
//	{
//		ReadConsoleInput(_HANDLE_PARAM, &IN_REC, 1, &cc);
//		if (IN_REC.EventType == KEY_EVENT && ((KEY_EVENT_RECORD&)IN_REC.Event).bKeyDown)
//		{
//			krec = (KEY_EVENT_RECORD&)IN_REC.Event;
//			return true;
//		}
//	}
//	return false;
//}

//KEY_PRESS_EVENTS::Keyboard_Input Object_KeyBoard;
void keyCallBack(GLFWwindow * window, const int KeyState, const int scancode, const int action, const int mods)
{
	KEY_PRESS_EVENTS::Keyboard_Input::SetKeyState(KeyState);
}

void updateInput(GLFWwindow * window, glm::vec3 & position, glm::vec3 & rotation, glm::vec3 & scale)
{
	KEY_PRESS_EVENTS::Keyboard_Input::updateInput_Key(window, position, rotation, scale);
}

int main(void)
{
	//KEY_PRESS_EVENTS::Keyboard_Input * Object_KeyBoard = new Keyboard_Input();
	//INIT GLFW
	glfwInit();

	//CREATE WINDOW
	const int WINDOW_WIDTH = 860;
	const int WINDOW_HEIGHT= 640;
	int framebufferWidth = 0;
	int framebufferHeight = 0;

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//4.4   major.minor
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	glfwWindowHint(GLFW_RESIZABLE, FALSE); //unresizable window

	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE); //for MAC OS

	GLFWwindow * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,"MY WINDOW", NULL, NULL);


	glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);

	//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	//glViewport(0, 0, framebufferWidth, framebufferHeight);

	glfwMakeContextCurrent(window);		//IMPORTANT!!

	//INIT GLEW (NEEDS WINDOW AND OPENGL CONTEXT)

	glewExperimental = GL_TRUE;

	//Error
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.COO::GLEW_INIT_FAILED" << '\n';
		glfwTerminate();
	}

	//OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//if u want draw it by lines
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//SHADER INIT
	Shader core_program("vertex_core.glsl", "fragment_core.glsl");
	//GLuint core_program;
	//if (!loadShaders(core_program))
	//{
	//	glfwTerminate();
	//}

	//MODEL MESH
	Mesh test(vertices, nrOfVertices, indices, nrOfIndices);

	/*VAO, VBO, EBO
	GENERATE VAO AND BIND*/
	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//GENERATE VAO AND BIND AND SEND DATA
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);	//if u want change it dynamically
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//GENERATE EBO AND BIND AND SEND DATA
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);  //if u want change it dynamically
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//SET VERTEXATTRIBPOINTERS AND ENABLE (INPUT ASSEMBLY)
	//[0][0.5][0][1][0][0][1][0][]
	//POSITION
	//GLuint attribLoc = glGetAttribLocation(core_program, "vertex_position");  if u dont have a shader location put where are zeros this attrib location
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid*)offsetof(Vertex, position));
	//[][][][][][][][][][][] ->VERTEX
	glEnableVertexAttribArray(0);

	//COLOR
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	//Texcoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
	glEnableVertexAttribArray(2);

	//Normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(3);

	//BIND VAO 0
	glBindVertexArray(0);

	Texture texture_0("IMAGES/simpson.png", GL_TEXTURE_2D, 0);

	////TEXTURE INIT 0
	//int image_width = 0;
	//int image_height = 0;
	//unsigned char* image = SOIL_load_image("IMAGES/simpson.png", &image_width, &image_height, nullptr, SOIL_LOAD_RGB);
	////unsigned char* image = SOIL_load_image("IMAGES/sunset.png", &image_width, &image_height, NULL, SOIL_LOAD_RGB);

	//GLuint texture0; //0 means ID oh the image
	//glGenTextures(1, &texture0);
	//glBindTexture(GL_TEXTURE_2D, texture0);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//magnify pixels 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					//minimalize pixels

	//if (image)
	//{
	//	std::cerr << "TEXTURE_LOADED" << '\n';
	//	std::cerr << image << '\n';
	//	std::cerr << image_width << '\n';
	//	std::cerr << image_height << '\n';*/
	//	assert(image != NULL);
	//	assert(image_width != NULL);
	//	assert(image_height != NULL);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);	//char is also a byte
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	glDisable(GL_CULL_FACE);		//to enable double side texture
	//}
	//else
	//{
	//	std::cerr << "ERROR::TEXTURE_LOADING_FAILED" << '\n';
	//}

	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);	//0 means 0 no active binde texture, 0 texture in there
	//SOIL_free_image_data(image);

	

	////TEXTURE INIT 1
	Texture texture_1("IMAGES/mesh.png", GL_TEXTURE_2D, 1);
	//int image_width_1 = 0;
	//int image_height_1 = 0;
	//unsigned char* image_1 = SOIL_load_image("IMAGES/mesh.png", &image_width_1, &image_height_1, nullptr, SOIL_LOAD_RGB);
	////unsigned char* image = SOIL_load_image("IMAGES/sunset.png", &image_width, &image_height, NULL, SOIL_LOAD_RGB);

	//GLuint texture1; //0 means ID oh the image
	//glGenTextures(1, &texture1);
	//glBindTexture(GL_TEXTURE_2D, texture1);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	//S -> two coordinate, T -> one coordinate
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);		//magnify pixels 
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);					//minimalize pixels

	//if (image_1)
	//{
	//	std::cerr << "TEXTURE_LOADED" << '\n';
	//	/*	std::cerr << image << '\n';
	//		std::cerr << image_width << '\n';
	//		std::cerr << image_height << '\n';*/
	//	assert(image_1 != NULL);
	//	assert(image_width_1 != NULL);
	//	assert(image_height_1 != NULL);
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width_1, image_height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);	//char is also a byte
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//	glDisable(GL_CULL_FACE);
	//}
	//else
	//{
	//	std::cerr << "ERROR::TEXTURE_LOADING_FAILED" << '\n';
	//}

	//glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, 0);	//0 means 0 no active binde texture, 0 texture in there
	//SOIL_free_image_data(image_1);


	//MATERIAL 0
	Material material0(glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), texture_0.get_texture_unit(), texture_1.get_texture_unit());


	//MATRIX MODEL, init MATRICES
	glm::vec3 position(0.f);
	glm::vec3 rotation(0.f);
	glm::vec3 scale(1.f);


	glm::mat4 ModelMatrix(1.f);
	ModelMatrix = glm::translate(ModelMatrix, position);
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x) ,glm::vec3(1.f, 0.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y) ,glm::vec3(0.f, 1.f, 0.f));
	ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z) ,glm::vec3(0.f, 0.f, 1.f));
	ModelMatrix = glm::scale(ModelMatrix, scale);

	//Camera, view and position
	glm::vec3 camPosition(0.f, 0.f, 1.f);
	glm::vec3 worldUp(0.f, 1.f, 0.f);
	glm::vec3 camFront(0.f, 0.f, -1.f);
	glm::mat4 ViewMatrix(1.f);
	ViewMatrix = glm::lookAt(camPosition, camPosition + camFront, worldUp);

	float fov = 90.f;	//its a angle between a object and camera bodu
	float nearPlane = 0.1f;
	float farPlane = 1000.f;
	glm::mat4 ProjectionMatrix(1.f);
	ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferWidth) / framebufferHeight, nearPlane, farPlane);


	//LIGHTS
	glm::vec3 lightPos0(0.f, 0.f, 1.f);


	//init uniforms
	//glUseProgram(core_program);
	//core_program.use();

	//Move, rotate and scale
	core_program.setMat4fv(ModelMatrix, "ModelMatrix");
	core_program.setMat4fv(ViewMatrix, "ViewMatrix");
	core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");
	/*glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"),1,GL_FALSE, glm::value_ptr(ModelMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ViewMatrix"),1,GL_FALSE, glm::value_ptr(ViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"),1,GL_FALSE, glm::value_ptr(ProjectionMatrix));*/

	core_program.setVec3f(lightPos0, "lightPos0");
	core_program.setVec3f(camPosition, "cameraPos");
	/*glUniform3fv(glGetUniformLocation(core_program, "lightPos0"), 1, glm::value_ptr(lightPos0));
	glUniform3fv(glGetUniformLocation(core_program, "cameraPos"), 1, glm::value_ptr(camPosition));*/

	glUseProgram(0);

	//MAIN LOOP
	//KEY_PRESS_EVENTS::Keyboard_Input  Obj();	//explicit basic constructor
	while (!glfwWindowShouldClose(window))
	{
		glfwSetKeyCallback(window, keyCallBack);
		updateInput(window, position, rotation, scale);
		//Object_KeyBoard.updateInput_Key(window, position, rotation, scale);
		//UPDATE INPUT ----
		//glfwWindowShouldClose(window,true)
		glfwPollEvents();
		//UPDATE ----
		//updateInput(window);  //only created event for esc key
		//updateInput(window,position,rotation,scale);
		//Obj.updateInput_Key(window, position, rotation, scale);

		//DRAW ----
		//Clear
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//Use a program //IMPORTANT SENT THE PROGRAM BEFORE SENDING THE UNIFORMS!!
		//glUseProgram(core_program);
	

		//Update uniforms
	/*	glUniform1i(glGetUniformLocation(core_program,"texture0"),0);
		glUniform1i(glGetUniformLocation(core_program,"texture1"),1);*/
		core_program.set1i(texture_0.get_texture_unit(), "texture0");
		core_program.set1i(texture_1.get_texture_unit(), "texture1");

		material0.sendToShader(core_program);

		//Move, rotation and scale in loop
		//position.z -= 0.1f;
		//rotation.y += 2.f;
		//scale.x += 0.001f;

		ModelMatrix = glm::mat4(1.f);
		ModelMatrix = glm::translate(ModelMatrix, position);	//your vector of matrix
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));	//rotate of X Axis
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));	//rotate of Y Axis
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));	//rotate of Z Axis
		ModelMatrix = glm::scale(ModelMatrix, scale);
	//	glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		core_program.setMat4fv(ModelMatrix, "ModelMatrix");

		//glfwGetFramebufferSize(window, &framebufferWidth, &framebufferWidth);

		//ProjectionMatrix = glm::mat4(1.f);
		ProjectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>((framebufferWidth) / framebufferHeight), nearPlane, farPlane);
		
		//glUniformMatrix4fv(glGetUniformLocation(core_program, "ProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
		core_program.setMat4fv(ProjectionMatrix, "ProjectionMatrix");

		//resizer of window
		//framebuffer_resize_callback(window, framebufferWidth, framebufferHeight);

		//Use program //START BEFORE U STOP DRAWING!!!!!!!!!
		core_program.use();


		//Update Uniforms

		//Activate texture
		texture_0.bind();
		texture_1.bind();
		/*glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);*/
		/*glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);*/

		//Bind vertex array object
		glBindVertexArray(VAO);


		////Draw both draw a triangle
		//glDrawArrays(GL_TRIANGLES, 0, nrOfVertices);		//drawing by vertices
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);	//drawing by indices
		test.render(&core_program);
		//system("pause");
		//End draw
		glfwSwapBuffers(window);
		glFlush();

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	//END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	//DELETE PROGRAM
	//glDeleteProgram(core_program);

	//system("pause");
	return EXIT_SUCCESS;
}