#include "Bullet.h"

Bullet::Bullet() : MinimalEntity(ZERO_VECTOR, ZERO_VECTOR, {50.0f, 50.0f}, "assets/game/bullet.png") {}

void Bullet::update(float deltaTime, std::vector<Monster * >& monsters){
    if (mAge > MAX_AGE){
        mVisibilityStatus = HIDDEN;
    }
    if (mVisibilityStatus == VISIBLE) {
        mPosition += mDirection * (deltaTime * BULLET_SPEED);
        mAge      += deltaTime;

        for (Monster * monster: monsters){
            if (monster->isActive()){
                float xDistance = fabs(mPosition.x - monster->getPosition().x) - 
                    ((mColliderDimensions.x + monster->getColliderDimensions().x) / 2.0f);
                float yDistance = fabs(mPosition.y - monster->getPosition().y) - 
                    ((mColliderDimensions.y + monster->getColliderDimensions().y) / 2.0f);

                if (xDistance < 0.0f && yDistance < 0.0f) {
                    // BULLET HIT ENEMY, DECR HP AND DESPAWN BULLET
                    monster->decrHP(1);
                    mVisibilityStatus = HIDDEN;
                    break;
                }
            }
        }
    }
}