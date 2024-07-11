#pragma once
#include "Program.h"
#include "TextCharacter.h"
#include <map>

class ProgramText : public Program
{
private:
	map<GLchar, TextCharacter> charactersMap;
	GLuint textColorId;
	unsigned int vao;
	unsigned int vbo;
public:
	ProgramText() {}

	GLuint getTextColorId() { return this->textColorId; }
	void initFreeType();
	void initUniforms();
	void initVao();
	void renderText(string text, float x, float y, float scale, vec3 color);
};

