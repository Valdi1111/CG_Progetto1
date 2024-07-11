#include "MovingEntity.h"

void MovingEntity::move()
{
	this->addX(this->getDx());
	this->addY(this->getDy());
	this->addZ(this->getDz());
}

bool MovingEntity::collidesWith(MovingEntity* e1)
{
	return sqrt(pow(e1->getX() - this->getX(), 2) + pow(e1->getY() - this->getY(), 2)) < e1->getHitbox() + this->getHitbox();
}