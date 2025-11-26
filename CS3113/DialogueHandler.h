#ifndef DIALOGUE_HANDLER_H
#define DIALOGUE_HANDLER_H

#include "cs3113.h"
#include "MinimalEntity.h"

enum Character {VETERAN_JOE, SUSPICIOUS_SALESMAN, GRANDMAW, DISH, MYSTERY}; 

struct DialogueLine {
    const char * text;
    Character character;
    int animIndex;
    float res; 
};

class DialogueHandler : public MinimalEntity
{
    private:
        std::map<Character, Texture2D> mIconsMap;

        int mCurrentLine = 0;

    public:
        // This is the lines used in the opening scene
        std::vector<DialogueLine> mDialogueLines = {
            {"Mysterious Individual: I must inform\n you that your grandmother has\n contracted Eternal Sleep disease", Character::MYSTERY, 0, 32.0f},
            {"As the name suggests, \nit makes you sleep forever", Character::MYSTERY, 0, 32.0f},
            {"Thankfully there is a cure...", Character::MYSTERY, 0, 32.0f},
            {"...", Character::MYSTERY, 0, 32.0f},
            {"Make \"the dish that\npleases the gods\"", Character::MYSTERY, 0, 32.0f},
            {"With legendary crops", Character::MYSTERY, 0, 32.0f},
            {"Good luck lol XD", Character::MYSTERY, 0, 32.0f},
        };

        using MinimalEntity::MinimalEntity;
        ~DialogueHandler();

        void jumpToNextText(); 

        void setDialogueLines(std::vector<DialogueLine> dialogLines) {mDialogueLines = dialogLines; mCurrentLine = 0; }

        void loadCharacterTexture(const char * filepath, const Character character);

        // Display text with the text, character, animation index;
        void displayText(const char * text, Character character, int animIndex, float res);

        // Doesn't need an update
        void update(float deltaTime) {}
        void render()     
        { 
            if (mVisibilityStatus == HIDDEN) return;
            displayText(
                mDialogueLines[mCurrentLine].text,
                mDialogueLines[mCurrentLine].character,
                mDialogueLines[mCurrentLine].animIndex,
                mDialogueLines[mCurrentLine].res
            ); 
        }

        int getCurrentLine () const { return mCurrentLine; }
};

#endif 