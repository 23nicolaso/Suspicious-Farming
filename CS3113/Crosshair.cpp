#include "Crosshair.h"


Crosshair::Crosshair(Vector2 position, Vector2 scale, const char *textureFilepath) : mPosition {position}, mScale {scale}, mTexture {LoadTexture(textureFilepath)} {}

Crosshair::~Crosshair() { UnloadTexture(mTexture); };


void Crosshair::render()
{
    if(mCrosshairStatus == CROSSHAIR_HIDDEN) return;

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
        0, WHITE
    );
}