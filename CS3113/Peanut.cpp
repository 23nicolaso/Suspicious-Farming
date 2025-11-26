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

    // Progressively gets faster. My reason? love of the game! 
    switch(mHP){
        case 3:
            mAnimState = STAGE_1;
            mSpeed     = 50;
            break;
        case 2:
            mAnimState = STAGE_2;
            mSpeed     = 100;
            break;
        case 1:
            mAnimState = STAGE_3;
            mSpeed     = 200;
            break;
        default:
            break;
    }

    moveChangeTimer -= deltaTime;

    if (moveChangeTimer < 0) {
        moveChangeTimer = 1.0f;
        int random = GetRandomValue(1, 4);
        switch (random){
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

    if (mTextureType == ATLAS) 
        animate(deltaTime);
}