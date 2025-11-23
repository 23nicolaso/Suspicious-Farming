#include "Peanut.h"

const std::map<int, std::vector<int>> Peanut::PeanutAnimationAtlas = {
    {STAGE_1,  { 4, 5, 6, 7 }},
    {STAGE_2,  { 8, 9, 10, 11 }},
    {STAGE_3,  { 12, 13, 14, 15 }},
};

void Peanut::update(float deltaTime, Entity *player, Map *map, 
    Entity *collidableEntities, int collisionCheckCount) 
{
    if (mEntityStatus == INACTIVE) return;

    resetColliderFlags();

    switch(mHP){
        case 3:
            mAnimState = STAGE_1;
            break;
        case 2:
            mAnimState = STAGE_2;
            break;
        case 1:
            mAnimState = STAGE_3;
            break;
        default:
            break;
    }

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