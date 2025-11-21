#include "Bullet.h"

Bullet::Bullet() : SimpleEntity(ZERO_VECTOR, ZERO_VECTOR, {50.0f, 50.0f}, "assets/game/bullet.png") {}

void Bullet::update(float deltaTime){
    if (mAge > MAX_AGE){
        mVisibilityStatus = HIDDEN;
    }
    if (mVisibilityStatus == VISIBLE) {
        mPosition += mDirection * (deltaTime * BULLET_SPEED);
        mAge      += deltaTime;
    }
}