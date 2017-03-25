//Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

//User
#include "ShaderLoader.h"

static const GLfloat triangle[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

int main(){
	if(glfwInit() == GL_FALSE){
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	atexit(glfwTerminate);
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *const window(glfwCreateWindow(1024, 768, "Example", NULL, NULL));


	if(!window){
		std::cerr << "Failed to create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if(glewInit() != GLEW_OK){
		std::cerr << "Failed to initialize GLEW." << std::endl;
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = CreateProgram("SimpleVertexShader.vtshader", "SimpleFragmentShader.fmshader");

	GLuint vaID;
	glGenVertexArrays(1, &vaID);
	glBindVertexArray(vaID);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	double lastTime = glfwGetTime();
	unsigned int frameCount = 0;

	do{
		double currentTime = glfwGetTime();
		++frameCount;	

		if(currentTime - lastTime >= 1.0){
			std::cout << "FPS : " << frameCount << std::endl;
			frameCount = 0;
			lastTime = currentTime;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vaID);
	glDeleteProgram(programID);
}
