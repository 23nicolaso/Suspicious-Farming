#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include "DialogueHandler.h"

class NPC : public Entity
{
private:
    std::vector<DialogueLine> mDialogueLines = {};

public:
    NPC(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, std::map<int, 
        std::vector<int>> animationAtlas, EntityType entityType) : Entity(position, scale, textureFilepath, 
        textureType, spriteSheetDimensions, animationAtlas, entityType) {}

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount) override;

    const std::vector<DialogueLine>& getDialogLines() const { return mDialogueLines; }
    void setDialogLines(const std::vector<DialogueLine>& dialogueLines) {mDialogueLines = dialogueLines;}
};

#endif // GENERIC_MONSTER_H