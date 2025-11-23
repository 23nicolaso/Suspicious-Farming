#ifndef GENERIC_MONSTER_H
#define GENERIC_MONSTER_H

#include "Entity.h"

class Monster : public Entity
{
protected:
    int mHP = 5;

public:
    Monster(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<int, 
        std::vector<int>> animationAtlas, EntityType entityType) : Entity(position, scale, textureFilepath, 
        textureType, spriteSheetDimensions, animationAtlas, entityType) {}
         
    static constexpr int    DEFAULT_SIZE          = 250,
                            DEFAULT_SPEED         = 50,
                            DEFAULT_FRAME_SPEED   = 3;
    static constexpr float  Y_COLLISION_THRESHOLD = 0.5f;

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;

    void setHP(int newHP)             { 
        mHP = newHP;        
        if (mHP <= 0) deactivate();
    }
    void decrHP(int deltaHP)          { 
        mRedFlashTime = 0.2f;
        mHP -= deltaHP;      
        if (mHP <= 0) deactivate();
    }
    
};

#endif // GENERIC_MONSTER_H