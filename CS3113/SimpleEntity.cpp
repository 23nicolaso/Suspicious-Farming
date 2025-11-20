#include "SimpleEntity.h"

SimpleEntity::SimpleEntity(Vector2 position, Vector2 direction, Vector2 scale, const char *textureFilepath) : mPosition {position}, mDirection {direction}, mScale {scale}, mTexture {LoadTexture(textureFilepath)} {}

SimpleEntity::~SimpleEntity() { UnloadTexture(mTexture); };

void SimpleEntity::render()
{
    if(mVisibilityStatus == HIDDEN) return;

    Rectangle textureArea;
    // Whole texture (UV coordinates)
    textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // bottom-right corner (of texture)
        static_cast<float>(mTexture.width),
        static_cast<float>(mTexture.height)
    };

    // Destination rectangle – centred on gPosition
    Rectangle destinationArea = {
        mPosition.x,
        mPosition.y,
        static_cast<float>(mScale.x),
        static_cast<float>(mScale.y)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    // Render the texture on screen
    DrawTexturePro(
        mTexture, 
        textureArea, destinationArea, originOffset,
        mRotation, WHITE
    );
}