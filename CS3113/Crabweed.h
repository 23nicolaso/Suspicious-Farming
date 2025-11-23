#ifndef CRABWEED_H
#define CRABWEED_H

#include "Monster.h"

class Crabweed : public Monster
{
    private:
        const static std::map<int, std::vector<int>> CrabweedAnimationAtlas;
        float moveChangeTimer = 1.0f;

    public:
        enum AnimState {MOVING, HIDING};

        Crabweed(Vector2 position) : Monster(
            position, 
            Vector2{100.0f, 100.0f},
            "assets/game/crabweeds.png",
            ATLAS,
            Vector2{1, 5},
            CrabweedAnimationAtlas,
            NPC
        ) {}
        
        void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;
};

#endif