#include "Item.h"

Item::Item(ItemType itemType, Vector2 scale, int quantity, const char *textureFilepath) : 
    mItemType {itemType}, mScale(scale), mQuantity {quantity}, mTexture {LoadTexture(textureFilepath)} {}

Item::Item() : mItemType{AIR}, mScale{DEFAULT_SIZE}, mQuantity{0}, mTexture {LoadTexture("assets/game/air.png")} {}

Item::~Item() { UnloadTexture(mTexture); };

void Item::renderAtPosition(Vector2 position) const
{
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
        position.x,
        position.y,
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

    // Draw quantity if > 1
    if (mQuantity > 1){
        DrawText(TextFormat("%i", mQuantity), position.x+0.2*mScale.x, position.y+0.2*mScale.y, 30, WHITE);
    }
}