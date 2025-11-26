#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "cs3113.h"
#include "NPC.h"

class NPCManager
{
private:
    // store as pointers for polymorphism
    std::vector<NPC *> mNPCs;
    Vector2 mOrigin;

public:
    ~NPCManager();
    void spawnNPC(int npcID);
    void render();
    void update(float deltaTime, Map *map);
    void setOrigin(Vector2 origin) {mOrigin = origin;} 

    std::vector<NPC *>& getNPCs () { return mNPCs; }
};

#endif 