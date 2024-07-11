#include "MovingEntity.h"
#define PI 3.14159265358979323846

class Projectile : public MovingEntity
{
protected: 
    float r;
    int nTriangles;

    void draw(void);

public:
    Projectile(float r, int nTriangles) {
        this->r = r;
        this->nTriangles = nTriangles;
        this->setHitbox(r);
    }

    void initAll(void);
    void tick(int time);
};
