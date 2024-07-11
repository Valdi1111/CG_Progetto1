#include "Enemy.h"
#include "Window.h"

void Enemy::initAll(void)
{
	vec4 color1 = vec4(0.5f, 0.0f, 0.5f, 1.0f);
	vec4 color2 = vec4(0.5f, 0.5f, 0.5f, 1.0f);

	this->createHermiteShape(this->polygonal, vec3(0.0f, 0.0f, 0.0f), color1, color2);
	this->initVao();
}

void Enemy::draw(void)
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertices.size());
}

void Enemy::tick(int time)
{
	this->setAngle(this->getAngle() + 0.3f);
	this->move();
	if (this->getX() < 0) {
		this->setRemoveNext();
	}
}