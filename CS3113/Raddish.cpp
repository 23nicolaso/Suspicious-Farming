#include "Raddish.h"

const std::map<int, std::vector<int>> Raddish::RaddishAnimationAtlas = {
    {MOVING,  { 0, 1, 2 }}
};

void Raddish::update(float deltaTime, Entity *player, Map *map, 
    Entity *collidableEntities, int collisionCheckCount) 
{
    if (mEntityStatus == INACTIVE) return;

    resetColliderFlags();
    mMovement.x = (player -> getPosition().x > mPosition.x) ? 1 : -1;
    mMovement.y = (player -> getPosition().y > mPosition.y) ? 1 : -1;
    
    mVelocity.x = mMovement.x * mSpeed;
    mVelocity.y = mMovement.y * mSpeed;

    mPosition.y += mVelocity.y * deltaTime;
    checkCollisionY(collidableEntities, collisionCheckCount);
    checkCollisionY(map);

    mPosition.x += mVelocity.x * deltaTime;
    checkCollisionX(collidableEntities, collisionCheckCount);
    checkCollisionX(map);

    if (mRedFlashTime > 0.0f) mRedFlashTime -= deltaTime;

    if (mTextureType == ATLAS && (mIsAnimationBlocking || (!mIsAnimationBlocking && GetLength(mMovement) != 0))) 
        animate(deltaTime);
}