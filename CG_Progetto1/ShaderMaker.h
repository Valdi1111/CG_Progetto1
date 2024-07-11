#pragma once
#include <string>
#include <GL/glew.h>

using namespace std;

class ShaderMaker
{
private:
	ShaderMaker() {}

public:
	static char* readSource(string shaderFile);
	static GLuint initFromFile(string shaderFilename, GLenum type);
};

