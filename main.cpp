#include "Include.h"

static const Object::Vertex rectangleVertex[] = {
	Object::Vertex({0.5f, 0.5f}),
	Object::Vertex({0.5f, -0.5f}),
	Object::Vertex({-0.5f, -0.5f}),
	Object::Vertex({-0.5f, 0.5f})
};

int main(){
	if(glfwInit() == GL_FALSE){
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	atexit(glfwTerminate);
	
	Window mainWindow;

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = CreateProgram("SimpleVertexShader.vtshader", "SimpleFragmentShader.fmshader");

	const GLint aspectLoc = glGetUniformLocation(programID, "aspect");

	std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex, true));

	while(mainWindow.ShouldClose() == GL_FALSE){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programID);

		glUniform1f(aspectLoc, mainWindow.GetAspect());

		shape -> draw();

		mainWindow.SwapBuffers();
	}
}
