#include "MonsterManager.h"

void MonsterManager::spawnMonster(MonsterType type, Vector2 location){
    mEntities.emplace_back(
        new Monster(
            location, 
            Vector2{100.0f, 100.0f},
            "assets/game/peanut.png",
            ATLAS,
            Vector2{3, 4},
            ANIMATION_ATLAS,
            NPC,
            WANDERER
        )
    );
}

void MonsterManager::render(){
    for (const Entity * entity : mEntities){
        entity -> render();
    }
}

void MonsterManager::update(float deltaTime, Entity * player, Map *map){
    for (Entity * entity: mEntities){
        entity -> update(
            deltaTime,
            player,
            map,
            nullptr,
            0
        );
    }
}