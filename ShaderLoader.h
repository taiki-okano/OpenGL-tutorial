#pragma once

//Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//OpenGL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

GLuint CreateProgram(const char* vt_path, const char* fm_path);

GLboolean PrintShaderInfoLog(const GLuint shader, const char* shaderName);

GLboolean PrintProgramInfoLog(const GLuint program);
