#include "Monster.h"

void Monster::AIWander() {}

void Monster::AIFollow(Entity *target)
{
    switch (mAIState)
    {
    case IDLE:
        if (Vector2Distance(mPosition, target->getPosition()) < 250.0f) 
            mAIState = WALKING;
        break;

    case WALKING:
        // Depending on where the player is in respect to their x-position
        // Change AnimState of the enemy
        if (mPosition.x > target->getPosition().x) moveLeft();
        else                                       moveRight();

        if (mPosition.y < target->getPosition().x) moveUp();
        else                                       moveDown();
    
    default:
        break;
    }
}

void Monster::AIActivate(Entity *target)
{
    switch (mAIType)
    {
    case WANDERER:
        AIWander();
        break;

    case FOLLOWER:
        AIFollow(target);
        break;
    
    default:
        break;
    }
}

void Monster::update(float deltaTime, Entity *player, Map *map, 
    Entity *collidableEntities, int collisionCheckCount) 
{
    if (mEntityStatus == INACTIVE) return;
    
    if (mEntityType == NPC) AIActivate(player);

    resetColliderFlags();

    mVelocity.x = mMovement.x * mSpeed;
    mVelocity.y = mMovement.y * mSpeed;

    mPosition.y += mVelocity.y * deltaTime;
    checkCollisionY(collidableEntities, collisionCheckCount);
    checkCollisionY(map);

    mPosition.x += mVelocity.x * deltaTime;
    checkCollisionX(collidableEntities, collisionCheckCount);
    checkCollisionX(map);

    if (mTextureType == ATLAS && (mIsAnimationBlocking || (!mIsAnimationBlocking && GetLength(mMovement) != 0))) 
        animate(deltaTime);
}