#include "Player.h"

const std::map<int, std::vector<int>> Player::playerAnimationAtlas = {
    {RIGHT_SLASH,  { 25, 26, 27, 28, 29 }},
    {LEFT_SLASH,   { 30, 31, 32, 33, 34 }},
    {DOWN,         { 1,  0,  1,  2  }},
    {LEFT,         { 10, 9,  10, 11 }},
    {UP,           { 4,  3,  4,  5  }},
    {RIGHT,        { 7,  6,  7,  8  }},
    {UP_HOLDING,   { 12, 13, 14, 13 }},
    {LEFT_HOLDING, { 18, 19, 20, 19 }},
    {RIGHT_HOLDING,{ 15, 16, 17, 16 }},
    {DOWN_HOLDING, { 40, 39, 40, 41 }},
    {DOWN_SLASH,   { 21, 22, 23, 24 }},
    {UP_SLASH,     { 35, 36, 37, 38 }},
    {DOWN_GUN,     { 42, 43, 44, 43 }},
    {RIGHT_GUN,    { 45, 46, 47, 46 }},
    {UP_GUN,       { 51, 52, 53, 52 }},
    {LEFT_GUN,     { 48, 49, 50, 49 }},
    {LEFT_SHOOT,   { 49, 55, 49 }},
    {RIGHT_SHOOT,  { 46, 54, 46 }},
    {UP_SHOOT,     { 52, 57, 52 }},
    {DOWN_SHOOT,   { 43, 56, 43 }}
};

void Player::useItem(MonsterManager * monsterManager, BulletManager * bulletManager, Map * map, ItemType activeItemType, Vector2 mousePosition){
    if (activeItemType == HOE){
        if (mIsAnimationBlocking){
            // Can't double block!
            return;
        }

        // HANDLE ANIMATION
        mCurrentFrameIndex = 0;
        mIsAnimationBlocking = true;
        if (abs(mousePosition.x) > 
            abs(mousePosition.y))
        {
            if (mousePosition.x > 0) mAnimState = RIGHT_SLASH;
            else                     mAnimState = LEFT_SLASH;
        } else {
            if (mousePosition.y > 0) mAnimState = DOWN_SLASH;
            else                     mAnimState = UP_SLASH;
        }

        // CORRECT MOUSE POSITION FOR WORLD
        mousePosition.x += mPosition.x;
        mousePosition.y += mPosition.y;

        // HANDLE MAP ADJUSTMENT
        if (map->getTileAt(mousePosition) == 3 && Vector2Distance(mousePosition, mPosition) < 150.0f) {
            map->setTileAt(mousePosition, 4);
        }

    }

    else if (activeItemType == GUN){
        if (mIsAnimationBlocking){
            // Can't double block!
            return;
        }

        mCurrentFrameIndex = 0;
        mIsAnimationBlocking = true;
        if (abs(mousePosition.x) > 
            abs(mousePosition.y))
        {
            if (mousePosition.x > 0) {
                mAnimState = RIGHT_SHOOT;
                bulletManager -> shoot(
                    {1.0f, 0.0f}, 
                    {mPosition.x + BULLET_SPAWN_OFFSET, mPosition.y}
                );
            }
            else {
                mAnimState = LEFT_SHOOT;
                bulletManager -> shoot(
                    {-1.0f, 0.0f}, 
                    {mPosition.x - BULLET_SPAWN_OFFSET, mPosition.y}
                );
            }
        } else {
            if (mousePosition.y > 0) {
                mAnimState = DOWN_SHOOT;
                bulletManager -> shoot(
                    {0.0f, 1.0f}, 
                    {mPosition.x, mPosition.y + BULLET_SPAWN_OFFSET}
                );
            }
            else {
                mAnimState = UP_SHOOT;
                bulletManager -> shoot(
                    {0.0f, -1.0f}, 
                    {mPosition.x, mPosition.y - BULLET_SPAWN_OFFSET}
                );
            }
        }
    }

    else if (activeItemType == CONSUMABLE){
        // CORRECT MOUSE POSITION FOR WORLD
        mousePosition.x += mPosition.x;
        mousePosition.y += mPosition.y;

        // will be more sophisticated in future, but for now just spawn the monster!
        monsterManager->spawnMonster(PEANUT, mousePosition);
    }
}

void Player::lookAtMouse(ItemType activeItemType, Vector2 mousePosition)
{
    if (mIsAnimationBlocking) return;

    if (activeItemType == GUN){
        if (abs(mousePosition.x) > 
            abs(mousePosition.y))
        {
            if (mousePosition.x > 0) mAnimState = RIGHT_GUN;
            else                     mAnimState = LEFT_GUN;
        } else {
            if (mousePosition.y > 0) mAnimState = DOWN_GUN;
            else                     mAnimState = UP_GUN;
        }
    }
    else {
        return;
    }
}