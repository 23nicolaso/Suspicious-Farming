#ifndef PEANUT_H
#define PEANUT_H

#include "Monster.h"

class Peanut : public Monster
{
    private:
        float moveChangeTimer = 1.0f;
        const static std::map<int, std::vector<int>> PeanutAnimationAtlas;

    public:
        enum AnimState {STAGE_1, STAGE_2, STAGE_3};

        Peanut(Vector2 position) : Monster(
            position, 
            Vector2{100.0f, 100.0f},
            "assets/game/peanut.png",
            ATLAS,
            Vector2{1, 16},
            PeanutAnimationAtlas,
            MONSTER,
            PEANUT
        ) {}
        
        void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;
};

#endif