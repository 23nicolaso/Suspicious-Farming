#include "NPC.h"

void NPC::update(float deltaTime, Entity *player, Map *map, 
    Entity *collidableEntities, int collisionCheckCount) 
{
    if (mEntityStatus == INACTIVE) return;

    resetColliderFlags();

    mVelocity.x = mMovement.x * mSpeed;
    mVelocity.y = mMovement.y * mSpeed;

    mPosition.y += mVelocity.y * deltaTime;
    checkCollisionY(map);

    mPosition.x += mVelocity.x * deltaTime;
    checkCollisionX(map);

    if (mTextureType == ATLAS && (mIsAnimationBlocking || (!mIsAnimationBlocking && GetLength(mMovement) != 0))) 
        animate(deltaTime);
}