#ifndef BULLET_MANAGER_H
#define BULLET_MANAGER_H

#include "Bullet.h"

class BulletManager
{
private:
    Bullet bullets[10];

public:
    void shoot(Vector2 direction, Vector2 spawnPosition);
    void update(float deltaTime);
    void render();
};

#endif 