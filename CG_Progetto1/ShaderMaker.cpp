#include "ShaderMaker.h"
#include <fstream>
#include <iostream>
#include <string>
#include <GL/glew.h>

using namespace std;

#pragma warning(disable:4996)
char* ShaderMaker::readSource(string shaderFile)
{
	string filePath = "shaders/" + shaderFile;
	FILE* fp = fopen(filePath.c_str(), "rb");
	if (fp == NULL) {
		return NULL;
	}

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);

	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);

	buf[size] = '\0';
	fclose(fp);

	return buf;
}

GLuint ShaderMaker::initFromFile(string shaderFilename, GLenum type)
{
	// Leggiamo il codice dello Shader
	GLchar* shaderSource = readSource(shaderFilename);

	GLuint shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, (const char**)&shaderSource, NULL);
	glCompileShader(shaderId);

	// Compiliamo lo shader
	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
		cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << endl;
	}
	return shaderId;
}