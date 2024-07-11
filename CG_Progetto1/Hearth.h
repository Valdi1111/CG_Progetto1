#pragma once
#include "Entity.h"

class Hearth : public Entity
{
protected:
    float rx;
    float ry;
    int nTriangles;

    void draw(void);

public:
    Hearth(float rx, float ry, int nTriangles) {
        this->rx = rx;
        this->ry = ry;
        this->nTriangles = nTriangles;
    }

    void initAll(void);
    void tick(int time);
};

