#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "MonsterManager.h"
#include "BulletManager.h"

enum AnimState    { 
    LEFT, UP, RIGHT, DOWN, UP_HOLDING, RIGHT_HOLDING, LEFT_HOLDING, 
    DOWN_SLASH, RIGHT_SLASH, UP_SLASH, DOWN_HOLDING, DOWN_GUN, LEFT_GUN,
    LEFT_SLASH, RIGHT_GUN, UP_GUN, LEFT_SHOOT, RIGHT_SHOOT, DOWN_SHOOT, UP_SHOOT              
}; 

class Player : public Entity
{
    private:
        static const std::map<int, std::vector<int>> playerAnimationAtlas;

    public:
    Player(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions,
        EntityType entityType) : 
        Entity(position, scale, textureFilepath, textureType, 
            spriteSheetDimensions, playerAnimationAtlas, entityType) {}

    static constexpr float  BULLET_SPAWN_OFFSET   = 50.0f;

    void moveUp    (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.y = -1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = UP;
        else if (heldItem == CONSUMABLE)            mAnimState = UP_HOLDING;
    }
    void moveDown  (ItemType heldItem) {
        if (mIsAnimationBlocking) return; 
        mMovement.y =  1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = DOWN;
        else if (heldItem == CONSUMABLE)            mAnimState = DOWN_HOLDING;
    }
    void moveLeft  (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x = -1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = LEFT;
        else if (heldItem == CONSUMABLE)            mAnimState = LEFT_HOLDING;
    }
    void moveRight (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x =  1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = RIGHT;
        else if (heldItem == CONSUMABLE)            mAnimState = RIGHT_HOLDING;
    }
    
    void lookAtMouse(ItemType activeItemType, Vector2 mousePosition);
    void useItem(MonsterManager * monsterManager, BulletManager * bulletManager, Map * map, ItemType activeItemType, Vector2 mousePosition);
};

#endif // PLAYER_H