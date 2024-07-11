#include "Background.h"

void Background::initAll(void)
{
	this->vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
	this->vertices.push_back(vec3(this->width / 2, -this->height / 2, 0.0f));
	this->vertices.push_back(vec3(this->width / 2, this->height / 2, 0.0f));
	this->vertices.push_back(vec3(-this->width / 2, this->height / 2, 0.0f));
	this->vertices.push_back(vec3(-this->width / 2, -this->height / 2, 0.0f));
	this->vertices.push_back(vec3(this->width / 2, -this->height / 2, 0.0f));
	
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	this->colors.push_back(vec4(0.0f, 0.0f, 0.0f, 0.0f));

	this->initVao();
}

void Background::draw(void)
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertices.size());
}

void Background::tick(int time)
{
}