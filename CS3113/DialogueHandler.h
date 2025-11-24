#ifndef DIALOGUE_HANDLER_H
#define DIALOGUE_HANDLER_H

#include "cs3113.h"
#include "MinimalEntity.h"

enum Character {VETERAN_JOE, SUSPICIOUS_SALESMAN}; 

class DialogueHandler : public MinimalEntity
{
    private:
        struct DialogueLine {
            const char * text;
            const Character character;
            const int animIndex;
            const float res; 
        };

        std::map<Character, Texture2D> mIconsMap;
        std::vector<DialogueLine> mDialogueLines = {
            { "Hello there!", VETERAN_JOE, 7, 32.0f},
            { "Hello there?", VETERAN_JOE, 5, 32.0f},
            { "Hello there T-T", VETERAN_JOE, 4, 32.0f},
            { "Hello there?!?", VETERAN_JOE, 3, 32.0f},
        };

        int mCurrentLine = 0;

    public:
        using MinimalEntity::MinimalEntity;
        ~DialogueHandler();

        void jumpToNextText(); 

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
};

#endif 