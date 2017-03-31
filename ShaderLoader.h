#pragma once

#include "Include.h"

GLuint CreateProgram(const char* vt_path, const char* fm_path);

GLboolean PrintShaderInfoLog(const GLuint shader, const char* shaderName);

GLboolean PrintProgramInfoLog(const GLuint program);
