#pragma once
#include "MovingEntity.h"

class LivingEntity : public MovingEntity
{
protected:
	bool dead = false;
public: 
	bool isDead() { return this->dead; }
	void die() { this->dead = true; }
};

