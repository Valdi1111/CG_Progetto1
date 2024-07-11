#pragma once
#include "LivingEntity.h"

class Player : public LivingEntity
{
protected:
    vector<vec3> polygonal;
    long lastShotTime = 0;
    int lives = Player::getMaxLives();
    int points = 0;

    void draw(void);

public:
    Player(vector<vec3> polygonal) {
        this->polygonal = polygonal;
        this->setHitbox(50);
        this->setShiftX(-155);
    }

    void initAll(void);
    void tick(int time);

    static long getShotCooldown() { return 1000; }
    long getLastShotTime() { return this->lastShotTime; }
    void setLastShotTime(long time) { this->lastShotTime = time; }

    static long getMaxLives() { return 5; }
    long getLives() { return this->lives; }
    void decreaseLives();

    int getPoints() { return this->points; }
    void addPoints(int points) { this->points += points; }
};

