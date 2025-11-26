#ifndef GENERIC_MONSTER_H
#define GENERIC_MONSTER_H

#include "Entity.h"

enum MonsterType {PEANUT, CRABWEED, RADDISH}; // ONLY THESE FOR NOW! 

class Monster : public Entity
{
protected:
    int mHP = 5;
    // ONLY CERTAIN MONSTERS CAN SET THIS LOL
    bool mIsInvincible = false; 
    bool mWasRewardGranted = false;
    MonsterType mMonsterType;

public:
    Monster(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<int, 
        std::vector<int>> animationAtlas, EntityType entityType, MonsterType monsterType) : Entity(position, scale, textureFilepath, 
        textureType, spriteSheetDimensions, animationAtlas, entityType), mMonsterType(monsterType) {}
         
    static constexpr int    DEFAULT_SIZE          = 250,
                            DEFAULT_SPEED         = 50,
                            DEFAULT_FRAME_SPEED   = 3;
    static constexpr float  Y_COLLISION_THRESHOLD = 0.5f;

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;

    void setHP(int newHP)             { 
        if (mIsInvincible) { return; }
        mHP = newHP;        
        if (mHP <= 0) deactivate();
    }
    void decrHP(int deltaHP)          { 
        if (mIsInvincible) { return; }
        mRedFlashTime = 0.2f;
        mHP -= deltaHP;      
        if (mHP <= 0) deactivate();
    }
    bool wasRewardGranted() const { return mWasRewardGranted; }
    void setRewardGranted()       { mWasRewardGranted = true; }
    MonsterType getMonsterType() const { return mMonsterType; }
};

#endif // GENERIC_MONSTER_H