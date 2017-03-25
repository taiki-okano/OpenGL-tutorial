#include "ShaderLoader.h"

GLuint CreateProgram(const char* vt_path, const char* fm_path){
	const GLuint programId = glCreateProgram();
	const GLuint vtShaderId = glCreateShader(GL_VERTEX_SHADER);
	const GLuint fmShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vtShaderCode;
	std::ifstream vtShaderStream(vt_path, std::ios::in);
	if(vtShaderStream.is_open()){
		std::string line = "";
		while(getline(vtShaderStream, line)){
			vtShaderCode += line + '\n';		
		}
		vtShaderStream.close();

		std::cout << "Compiling shader : " << vt_path << std::endl;
		char const* vtShaderCodePointer = vtShaderCode.c_str();
		glShaderSource(vtShaderId, 1, &vtShaderCodePointer, NULL);
		glCompileShader(vtShaderId);
	}
	else{
		std::cerr << "Failed to open : " << vt_path << std::endl;
	}

	std::string fmShaderCode;
	std::ifstream fmShaderStream(fm_path, std::ios::in);
	if(fmShaderStream.is_open()){
		std::string line = "";
		while(getline(fmShaderStream, line)){
			fmShaderCode += line + '\n';		
		}
		fmShaderStream.close();

		std::cout << "Compiling shader : " << fm_path << std::endl;
		char const* fmShaderCodePointer = fmShaderCode.c_str();
		glShaderSource(fmShaderId, 1, &fmShaderCodePointer, NULL);
		glCompileShader(fmShaderId);
	}
	else{
		std::cerr << "Failed to open : " << fm_path << std::endl;
	}

	if(PrintShaderInfoLog(vtShaderId, vt_path)){
		glAttachShader(programId, vtShaderId);
	}
	glDeleteShader(vtShaderId);
	if(PrintShaderInfoLog(fmShaderId, fm_path)){
		glAttachShader(programId, fmShaderId);
	}
	glDeleteShader(fmShaderId);

	std::cout << "Linking program and shaders" << std::endl;
	glLinkProgram(programId);

	if(PrintProgramInfoLog(programId)){
		return programId;
	}

	glDeleteProgram(programId);
	return 0;
}

GLboolean PrintShaderInfoLog(const GLuint shader, const char* shaderName){
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Compile error : " << shaderName << std::endl;
	}
	
	GLsizei bufSize;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

	if(bufSize){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}
	
	return static_cast<GLboolean>(status);
}

GLboolean PrintProgramInfoLog(const GLuint program){
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if(status == GL_FALSE){
		std::cerr << "Link error : " << std::endl;
	}
	
	GLsizei bufSize;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if(bufSize){
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}
