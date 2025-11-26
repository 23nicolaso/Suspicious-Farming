#ifndef MONSTER_MANAGER_H
#define MONSTER_MANAGER_H

#include "cs3113.h"
#include "Monster.h"
#include "Peanut.h"
#include "Crabweed.h"
#include "Raddish.h"
#include "Item.h"

class MonsterManager
{
private:
    // store as pointers for polymorphism
    std::vector<Monster *> mMonsters; 
    std::vector<Item *>    mUnredeemedDrops;

public:
    ~MonsterManager();

    void spawnMonster(MonsterType type, Vector2 location);
    void render();
    void update(float deltaTime, Entity * player, Map *map);

    std::vector<Monster *>& getMonsters () { return mMonsters; }
    std::vector<Item *>&    redeemDrops () { return mUnredeemedDrops; }
    void                    clearDrops  () { mUnredeemedDrops.clear();}
};

#endif 