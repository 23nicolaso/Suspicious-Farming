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
            map,
            nullptr,
            0
        );

        if (monster -> isActive() == false && monster -> wasRewardGranted() == false){
            monster -> setRewardGranted();
            // Should reward player by putting in the list of drops available for redemption
            if (monster->getMonsterType() == PEANUT){
                // REWARD PEANUT
                mUnredeemedDrops.emplace_back(new Item(
                    SELLABLE,
                    PEANUT_DROP,
                    {80.0f, 80.0f},
                    1,
                    "assets/game/peanut_item.png"
                ));
            }
            else if (monster->getMonsterType() == CRABWEED){
                // REWARD CRABWEED
                mUnredeemedDrops.emplace_back(new Item(
                    SELLABLE,
                    CRABWEED_DROP,
                    {80.0f, 80.0f},
                    1,
                    "assets/game/bundle_of_weeds.png"
                ));
            }
            else if (monster->getMonsterType() == RADDISH){
                // REWARD RADDISH
                mUnredeemedDrops.emplace_back(new Item(
                    SELLABLE,
                    RADDISH_DROP,
                    {80.0f, 80.0f},
                    1,
                    "assets/game/raddish_item.png"
                ));
            }
        }
    }
}