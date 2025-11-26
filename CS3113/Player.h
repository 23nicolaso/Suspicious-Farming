#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "MonsterManager.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "Crosshair.h"
#include "DialogueHandler.h"

class Player : public Entity
{
    private:
        Sound slashSound;
        Sound shootSound;
        Sound plantSound;
        const float ITEM_SCALE = 80.0f;

        static const std::map<int, std::vector<int>> playerAnimationAtlas;

    public:
    enum AnimState { 
        LEFT, UP, RIGHT, DOWN, UP_HOLDING, RIGHT_HOLDING, LEFT_HOLDING, 
        DOWN_SLASH, RIGHT_SLASH, UP_SLASH, DOWN_HOLDING, DOWN_GUN, LEFT_GUN,
        LEFT_SLASH, RIGHT_GUN, UP_GUN, LEFT_SHOOT, RIGHT_SHOOT, DOWN_SHOOT, UP_SHOOT,
        DANCE              
    }; 

    Player(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions,
        EntityType entityType) : 
        Entity(position, scale, textureFilepath, textureType, 
            spriteSheetDimensions, playerAnimationAtlas, entityType) {
                slashSound = LoadSound("assets/audio/slash.mp3");
                plantSound = LoadSound("assets/audio/crunch.mp3");
                shootSound = LoadSound("assets/audio/water_gun.mp3");
                SetSoundVolume(slashSound, 0.5f);
                SetSoundVolume(plantSound, 0.5f);
                SetSoundVolume(shootSound, 0.5f);
            }
    
    ~Player() { UnloadSound(slashSound); UnloadSound(plantSound); UnloadSound(shootSound);}

    static constexpr float  BULLET_SPAWN_OFFSET   = 50.0f;

    void moveUp    (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.y = -1; 
        if (heldItem != GUN)     mAnimState = UP;
    }
    void moveDown  (ItemType heldItem) {
        if (mIsAnimationBlocking) return; 
        mMovement.y =  1; 
        if (heldItem != GUN)     mAnimState = DOWN;
    }
    void moveLeft  (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x = -1; 
        if (heldItem != GUN)     mAnimState = LEFT;
    }
    void moveRight (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x =  1; 
        if (heldItem != GUN)     mAnimState = RIGHT;
    }
    
    void lookAtMouse(ItemType activeItemType, Vector2 mousePosition);
    void useItem(MonsterManager * monsterManager, BulletManager * bulletManager, Map * map, Map * plantMap, Inventory * inventory, ItemType activeItemType, Crosshair * crosshair, DialogueHandler * dialogueHandler,  Vector2 mousePosition);
};

#endif // PLAYER_H