#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "cs3113.h"
#include "Monster.h"
#include "Peanut.h"
#include "Crabweed.h"
#include "Raddish.h"

enum MonsterType {PEANUT, CRABWEED, RADDISH}; // ONLY THESE FOR NOW! 

class MonsterManager
{
private:
    // store as pointers for polymorphism
    std::vector<Monster *> mMonsters; 

public:
    ~MonsterManager();

    void spawnMonster(MonsterType type, Vector2 location);
    void render();
    void update(float deltaTime, Entity * player, Map *map);

    std::vector<Monster *>& getMonsters () { return mMonsters; }
};

#endif 