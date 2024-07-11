#pragma once
#include "Entity.h"
class Background : public Entity
{
protected:
    float width;
    float height;

    void draw(void);

public:
    Background(float width, float height) {
        this->width = width;
        this->height = height;
    }

    void initAll(void);
    void tick(int time);
};

