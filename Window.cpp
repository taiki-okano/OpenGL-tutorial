#include "Window.h"

Window::Window(const GLuint width, const GLuint height, const bool fullScreen, const char* title) : m_window(glfwCreateWindow(width, height, title, fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL)){
	if(m_window == NULL){
		std::cerr << "Failed to create the window" << std::endl;
		exit(1);
	}
	
	glfwMakeContextCurrent(m_window);

	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK){
		std::cerr << "Failed to initialize GLEW" << std::endl;
		exit(1);
	}

	glfwSetWindowUserPointer(m_window, this);

	glfwSwapInterval(1);

	glfwSetWindowSizeCallback(m_window, Resize);

	Resize(m_window, width, height);
}

Window::~Window(){
	glfwDestroyWindow(m_window);
}

int Window::ShouldClose() const{
	return glfwWindowShouldClose(m_window);
}

void Window::SwapBuffers(){
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

GLfloat Window::GetAspect() const{
	return m_aspect;
}

void Window::Resize(GLFWwindow *const window, const int width, const int height){
	glViewport(0, 0, width, height);

	Window *const instance = static_cast<Window *>(glfwGetWindowUserPointer(window));

	if(instance != NULL){
		instance -> m_aspect = static_cast<GLfloat>(width) / static_cast<GLfloat>(height);
	}
}
