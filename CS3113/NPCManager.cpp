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
            {"Grandpa: Did ya hear that?\n There's a way to cure grandmaw!", Character::VETERAN_JOE, 7, 32.0f},
            {"But it takes legendary crops :(", Character::VETERAN_JOE, 8, 32.0f},
            {"I heard the last time there was\n dem legendary crops\nwas 152 years ago", Character::VETERAN_JOE, 5, 32.0f},
            {"And it was by a once in a\n millenia legendary farmer", Character::VETERAN_JOE, 4, 32.0f},
            {"Maybe we won't be\nable to cure grandmaw", Character::VETERAN_JOE, 4, 32.0f},
            {"Suspicious Salesman: FEAR NOT!!!", Character::SUSPICIOUS_SALESMAN, 0, 32.0f},
            {"Grandpa: Now how the hell\ndid you get in my dialog box?", Character::VETERAN_JOE, 5, 32.0f},
            {"Suspicious Salesman: That is\n ... irrelevant", Character::SUSPICIOUS_SALESMAN, 0, 32.0f},
            {"Feast your eyes on this!!!", Character::SUSPICIOUS_SALESMAN, 1, 32.0f},
            {"I put suspicious\n fertilizer in this crop!", Character::SUSPICIOUS_SALESMAN, 2, 32.0f},
            {"Watch what it does", Character::SUSPICIOUS_SALESMAN, 3, 32.0f},
            {"And just like that. \nA legendary crop!!!", Character::SUSPICIOUS_SALESMAN, 4, 32.0f},
            {"Suspicious fertilizer turns\n any crop into a legendary\n crop by giving it a soul!", Character::SUSPICIOUS_SALESMAN, 4, 32.0f},
            {"I accept Bapple Pay,\n MasterBard or Cash. \n$15 covers your whole yard!", Character::SUSPICIOUS_SALESMAN, 5, 32.0f},
            {"Grandpa: ...", Character::VETERAN_JOE, 3, 32.0f},
            {"...", Character::VETERAN_JOE, 6, 32.0f},
            {"give me your whole supply.", Character::VETERAN_JOE, 6, 32.0f},
            {"my child. You must go farm now.", Character::VETERAN_JOE, 6, 32.0f},
            {"Disclaimer: \nSide Effects May Include:\n Aggression, Nausea, \n Stage 5 Cancer", Character::SUSPICIOUS_SALESMAN, 5, 32.0f},
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