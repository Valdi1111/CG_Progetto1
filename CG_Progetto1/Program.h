#pragma once
#include <string>
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
using namespace std;

class Program
{
protected:
	GLuint programId;
	GLuint projectionId;
public:
	Program() {}

	GLuint getProgramId() { return this->programId; }
	GLuint getProjectionId() { return this->projectionId; }
	void initProgram(string vertexFilename, string fragmentFilename);
	virtual void initUniforms() = 0;
	void switchProgram(mat4 projection);
};

