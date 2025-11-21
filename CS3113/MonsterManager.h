#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "cs3113.h"
#include "Monster.h"

enum MonsterType {PEANUT};

class MonsterManager
{
private:
    // only one entry for now cuz only one monster
    const std::map<MonsterType, AIType> monsterMappings = {{PEANUT, WANDERER}};
    // store as pointers for polymorphism
    std::vector<Entity *> mEntities; 

    const std::map<int, std::vector<int>> ANIMATION_ATLAS = {
        {ENTITY_DOWN, {0, 1, 2, 3}},
        {ENTITY_UP,   {0, 1, 2, 3}},
        {ENTITY_RIGHT,{0, 1, 2, 3}},
        {ENTITY_LEFT, {0, 1, 2, 3}}
    };

public:
    void spawnMonster(MonsterType type, Vector2 location);

    void render();
    void update(float deltaTime, Entity * player, Map *map);
};

#endif 