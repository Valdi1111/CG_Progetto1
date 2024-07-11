#pragma once
#include "MovingEntity.h"

class Enemy : public MovingEntity
{
protected:
    vector<vec3> polygonal;
    void draw(void);

public:
    Enemy(vector<vec3> polygonal) {
        this->polygonal = polygonal;
        this->setHitbox(30);
    }
    
    void initAll(void);
    void tick(int time);
};

