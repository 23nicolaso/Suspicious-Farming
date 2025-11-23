#include "DialogueHandler.h"

DialogueHandler::~DialogueHandler(){
    for (auto const& pair: mIconsMap){
        UnloadTexture(pair.second);
    }

    mIconsMap.clear();
}

void DialogueHandler::loadCharacterTexture(const char * filepath, const Character character){
    mIconsMap[character] = LoadTexture(filepath);
}

void DialogueHandler::displayText(const char * text, const Character character, int animIndex){
    if (mVisibilityStatus == HIDDEN) return;
    render();

    DrawText(text, mPosition.x - 300, mPosition.y, 80, BLACK);

    Rectangle textureArea;
    // Whole texture (UV coordinates)
    textureArea = {
        // top-left corner
        static_cast<float>(animIndex)*32.0f, 0.0f,

        // width and height
        32.0f,
        32.0f
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        mPosition.x-485.0f,
        mPosition.y,
        32.0f*20*0.4f,
        32.0f*20*0.4f
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        32.0f*10*0.4f,
        32.0f*10*0.4f
    };

    // Render the texture on screen
    DrawTexturePro(
        mIconsMap[character], 
        textureArea, destinationArea, originOffset,
        mRotation, WHITE
    );
}