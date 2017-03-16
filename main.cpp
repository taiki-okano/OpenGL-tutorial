//Standard Libraries
#include <iostream>
#include <memory>

//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

int main(){
	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::unique_ptr<GLFWwindow> window = glfwWindowCreate(1024, 768, "Example", NULL, NULL);
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
	
}
