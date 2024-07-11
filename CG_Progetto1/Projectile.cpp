#include "Projectile.h"
#include "Window.h"
#define PI 3.14159265358979323846

void Projectile::initAll(void) 
{
	this->vertices.push_back(vec3(0.0, 0.0, 0.0));
	this->colors.push_back(vec4(255.0 / 255.0, 75.0 / 255.0, 0.0, 1.0));
	float stepA = (2 * PI) / this->nTriangles;
	for (int i = 0; i <= this->nTriangles; i++)
	{
		float t = (float) i * stepA;
		this->vertices.push_back(vec3(0.0 + this->r * cos(t), 0.0 + this->r * sin(t), 0.0));
		this->colors.push_back(vec4(1.0, 204.0 / 255.0, 0.0, 1.0));
	}

	this->initVao();
}

void Projectile::draw(void)
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertices.size());
}

void Projectile::tick(int time)
{
	this->move();
	if (this->getX() > Window::getWidth()) {
		this->setRemoveNext();
	}
}
