#pragma once

#include "Include.h"

class Window{
	GLFWwindow *const m_window;
    GLuint m_width, m_height;
	GLfloat m_aspect;

public:
	Window(const GLuint width = 640, const GLuint height = 480, const bool fullScreen = false, const char* title = "Untitled");

	virtual ~Window();
	
	int ShouldClose() const;

	void SwapBuffers();

	GLfloat GetAspect() const;

	static void Resize(GLFWwindow *const window, const int width, const int height);
};
