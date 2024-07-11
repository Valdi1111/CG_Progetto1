#include "Hearth.h"
#define PI 3.14159265358979323846


void Hearth::initAll(void)
{
	this->vertices.push_back(vec3(0.0, 0.0, 0.0));
	this->colors.push_back(vec4(0.6, 0.0, 0.0, 1.0));
	float stepA = (2 * PI) / this->nTriangles;
	for (int i = 0; i <= this->nTriangles; i++)
	{
		float t = (float) i * stepA;
		this->vertices.push_back(vec3(0.0 + this->rx * (16 * pow(sin(t), 3)), 0.0 + this->ry * ((13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t))), 0.0));
		this->colors.push_back(vec4(1.0, 0.0, 0.0, 1.0));
	}
	this->initVao();
}

void Hearth::draw(void)
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertices.size());
}

void Hearth::tick(int time)
{
}