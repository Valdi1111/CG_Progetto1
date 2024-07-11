#include "Player.h"
#include "Window.h"

#define LIMIT_LEFT 0
#define LIMIT_RIGHT Window::getWidth() / 1.5f
#define LIMIT_BOTTOM 0
#define LIMIT_UP Window::getHeight()

void Player::initAll(void)
{
	vec4 color1 = vec4(20.0f / 255.0f, 80.0f / 255.0f, 75.0f / 255.0f, 1.0f);
	vec4 color2 = vec4(75.0f / 255.0f, 175.0f / 255.0f, 175.0f / 255.0f, 1.0f);

	this->createHermiteShape(this->polygonal, vec3(0.0f, 0.0f, 0.0f), color1, color2);
	this->initVao();
}

void Player::draw(void)
{
	glDrawArrays(GL_TRIANGLE_FAN, 0, this->vertices.size());
}

void Player::tick(int time)
{
	this->move();
	float half = this->getHitbox() / 2;
	if (this->getX() - half < LIMIT_LEFT && this->getDx() < 0) {
		this->setX(LIMIT_LEFT + half);
	}
	if (this->getX() + half > LIMIT_RIGHT && this->getDx() > 0) {
		this->setX(LIMIT_RIGHT - half);
	}
	if (this->getY() - half < LIMIT_BOTTOM && this->getDy() < 0) {
		this->setY(LIMIT_BOTTOM + half);
	}
	if (this->getY() + half > LIMIT_UP && this->getDy() > 0) {
		this->setY(LIMIT_UP - half);
	}
}

void Player::decreaseLives() 
{ 
	this->lives--;
	if (this->lives <= 0) {
		this->die();
	}
}
