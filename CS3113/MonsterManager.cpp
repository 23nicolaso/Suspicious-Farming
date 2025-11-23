#include "MonsterManager.h"

MonsterManager::~MonsterManager(){
    for (Monster * monster: mMonsters){
        delete monster;
    }

    mMonsters.clear();
}

void MonsterManager::spawnMonster(MonsterType type, Vector2 location){
    if (type == PEANUT){
        Peanut * monster = new Peanut(
            location
        );

        mMonsters.emplace_back(monster);
    }
    else if (type == CRABWEED){
        Crabweed * monster = new Crabweed(
            location
        );

        mMonsters.emplace_back(monster);
    }
    else if (type == RADDISH){
        Raddish * monster = new Raddish(
            location
        );

        mMonsters.emplace_back(monster);
    }
}

void MonsterManager::render(){
    for (const Monster * monster : mMonsters){
        monster -> render();
    }
}

void MonsterManager::update(float deltaTime, Entity * player, Map *map){
    for (Monster * monster: mMonsters){
        monster -> update(
            deltaTime,
            player,
            nullptr,
            nullptr,
            0
        );
    }
}