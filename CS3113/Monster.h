#ifndef GENERIC_MONSTER_H
#define GENERIC_MONSTER_H

#include "BaseEntity.h"

enum AIType       { WANDERER, FOLLOWER                  };
enum AIState      { WALKING, IDLE, FOLLOWING            };

class Monster : public Entity
{
private:
    AIType  mAIType;
    AIState mAIState;

    void AIActivate(Entity *target);
    void AIWander();
    void AIFollow(Entity *target);

public:
    Monster(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<int, 
        std::vector<int>> animationAtlas, EntityType entityType, AIType aiType) : Entity(position, scale, textureFilepath, 
        textureType, spriteSheetDimensions, animationAtlas, entityType), mAIType(aiType){}
         
    static constexpr int    DEFAULT_SIZE          = 250,
                            DEFAULT_SPEED         = 200,
                            DEFAULT_FRAME_SPEED   = 3;
    static constexpr float  Y_COLLISION_THRESHOLD = 0.5f;

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;

    AIType      getAIType()                const { return mAIType;                }
    AIState     getAIState()               const { return mAIState;               }

    void setAIState(AIState newState)
        { mAIState = newState;                     }
    void setAIType(AIType newType)
        { mAIType = newType;                       }
};

#endif // GENERIC_MONSTER_H