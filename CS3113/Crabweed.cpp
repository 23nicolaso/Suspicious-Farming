#include "Crabweed.h"

const std::map<int, std::vector<int>> Crabweed::CrabweedAnimationAtlas = {
    {MOVING,  { 0, 1, 2 }},
    {HIDING,  { 3, 4    }}
};

void Crabweed::update(float deltaTime, Entity *player, Map *map, 
    Entity *collidableEntities, int collisionCheckCount) 
{
    if (mEntityStatus == INACTIVE) return;

    resetColliderFlags();

    moveChangeTimer -= deltaTime;

    if (moveChangeTimer < 0) {
        moveChangeTimer = 1.0f;
        int random = GetRandomValue(0, 4);
        switch (random){
            case 0:
                // Toggle anim state
                mAnimState = mAnimState == HIDING? MOVING : HIDING;
                break;
            case 1:
                moveUp();
                break;
            case 2:
                moveRight();
                break;
            case 3:
                moveDown();
                break;
            case 4:
                moveLeft();
                break;
        }
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