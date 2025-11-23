#ifndef RADDISH_H
#define RADDISH_H

#include "Monster.h"

class Raddish : public Monster
{
    private:
        const static std::map<int, std::vector<int>> RaddishAnimationAtlas;

    public:
        enum AnimState {MOVING};

        Raddish(Vector2 position) : Monster(
            position, 
            Vector2{100.0f, 100.0f},
            "assets/game/raddish.png",
            ATLAS,
            Vector2{1, 3},
            RaddishAnimationAtlas,
            NPC
        ) {}
        
        void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;
};

#endif