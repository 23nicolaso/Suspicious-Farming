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

void DialogueHandler::displayText(const char * text, const Character character, int animIndex, float res){
    if (mVisibilityStatus == HIDDEN) return;

    Rectangle textureArea1;
    // Whole texture (UV coordinates)
    textureArea1 = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(mTexture.width),
        static_cast<float>(mTexture.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea1 = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mScale.x),
        static_cast<float>(mScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset1 = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        mTexture, 
        textureArea1, destinationArea1, originOffset1,
        mRotation, WHITE
    );

    DrawText(text, mPosition.x - 300, mPosition.y, 80, BLACK);

    Rectangle textureArea;
    // Whole texture (UV coordinates)
    textureArea = {
        // top-left corner
        static_cast<float>(animIndex)*res, 0.0f,

        // width and height
        res,
        res
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

void DialogueHandler::jumpToNextText(){
    mCurrentLine += 1;
    if (mCurrentLine >= mDialogueLines.size()){
        deactivate();
    }
}