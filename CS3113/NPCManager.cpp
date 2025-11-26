#include "NPCManager.h"

NPCManager::~NPCManager(){
    for (NPC * npc: mNPCs){
        delete npc;
    }

    mNPCs.clear();
}

void NPCManager::spawnNPC(int npcID){
    if (npcID == 0){
        NPC * npc = new NPC(
            Vector2{mOrigin.x-300.0f, mOrigin.y},
            Vector2{100.0f, 100.0f},
            "assets/game/veteranjoe.png",
            ATLAS,
            {1, 9},
            std::map<int, std::vector<int>>{{0, std::vector<int>{0,1,2}}},
            HUMAN_NPC
        );

        npc -> setDialogLines({
            {"Grandpa: I heard there's a\n way to cure grandmaw!", Character::VETERAN_JOE, 7, 32.0f},
            {"But it takes legendary crops :(", Character::VETERAN_JOE, 8, 32.0f},
            {"I heard the last time there was\n dem legendary crops\nwas 152 years ago", Character::VETERAN_JOE, 5, 32.0f},
            {"But you got this right?", Character::VETERAN_JOE, 7, 32.0f},
            {"Suspicious Salesman: FEAR NOT!!!", Character::SUSPICIOUS_SALESMAN, 0, 32.0f},
            {"Grandpa: Now how the hell\ndid you get in my dialog box?", Character::VETERAN_JOE, 5, 32.0f},
            {"Suspicious Salesman: That is\n ... irrelevant", Character::SUSPICIOUS_SALESMAN, 0, 32.0f},
            {"Feast your eyes on this!!!", Character::SUSPICIOUS_SALESMAN, 1, 32.0f},
            {"I put some suspicious\n fertilizer in a crop!", Character::SUSPICIOUS_SALESMAN, 2, 32.0f},
            {"Any day now...", Character::SUSPICIOUS_SALESMAN, 3, 32.0f},
            {"And just like that. \nA legendary crop!!!", Character::SUSPICIOUS_SALESMAN, 4, 32.0f},
            {"I accept Bapple Pay,\n MasterBard or Cash. \n$15 covers your whole yard!", Character::SUSPICIOUS_SALESMAN, 5, 32.0f},
            {"Grandpa: ...", Character::VETERAN_JOE, 3, 32.0f},
            {"Grandpa: ...", Character::VETERAN_JOE, 6, 32.0f},
            {"Grandpa: give me your whole supply.", Character::VETERAN_JOE, 6, 32.0f},
            {"Grandpa: my child. Go out and farm.", Character::VETERAN_JOE, 6, 32.0f},
        });
        
        mNPCs.emplace_back(npc);
    }
}

void NPCManager::render(){
    for (const Entity * npc : mNPCs){
        npc -> render();
    }
}

void NPCManager::update(float deltaTime, Map *map){
    for (Entity * npc: mNPCs){
        npc -> update(
            deltaTime,
            nullptr,
            map,
            nullptr,
            0
        );
    }
}