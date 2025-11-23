#ifndef DIALOGUE_HANDLER_H
#define DIALOGUE_HANDLER_H

#include "cs3113.h"
#include "MinimalEntity.h"

enum Character {VETERAN_JOE, SUSPICIOUS_SALESMAN}; 

class DialogueHandler : public MinimalEntity
{
    private:
        std::map<Character, Texture2D> mIconsMap;

    public:
        using MinimalEntity::MinimalEntity;
        ~DialogueHandler();

        void loadCharacterTexture(const char * filepath, const Character character);

        // Display text with the text, character, animation index;
        void displayText(const char * text, Character character, int animIndex);

        // Doesn't need an update
        void update(float deltaTime) {}
};

#endif 