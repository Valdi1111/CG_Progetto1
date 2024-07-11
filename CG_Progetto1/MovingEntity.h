#pragma once
#include "Entity.h"
class MovingEntity : public Entity
{
protected:
	int hitbox = 0;
	int dx = 0;
	int dy = 0;
	int dz = 0;

	void move();

public:
	MovingEntity() {}

	int getHitbox() const { return this->hitbox; }
	void setHitbox(int hitbox) { this->hitbox = hitbox; }

	int getDx() const { return this->dx; }
	int getDy() const { return this->dy; }
	int getDz() const { return this->dz; }

	void setDx(int dx) { this->dx = dx; }
	void setDy(int dy) { this->dy = dy; }
	void setDz(int dz) { this->dz = dz; }

	bool collidesWith(MovingEntity* e1);
};

