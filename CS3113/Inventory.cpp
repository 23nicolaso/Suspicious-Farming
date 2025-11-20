#include "Inventory.h"

Inventory::Inventory(Vector2 position, Vector2 scale, const char *textureFilepath) : mPosition {position}, mScale {scale}, mTexture {LoadTexture(textureFilepath)} {}

Inventory::~Inventory() { UnloadTexture(mTexture); };

void Inventory::render()
{
    Rectangle textureArea;
    Rectangle activeSlotTextureArea; 
    // Half texture, because texture has active/unactive slots
    textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // width and height
        static_cast<float>(mTexture.width / 2),
        static_cast<float>(mTexture.height)
    };

    activeSlotTextureArea = {
        // top-left corner
        static_cast<float>(mTexture.width / 2), 0.0f,

        // width and height
        static_cast<float>(mTexture.width / 2),
        static_cast<float>(mTexture.height)
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 originOffset = {
        static_cast<float>(mScale.x) / 2.0f,
        static_cast<float>(mScale.y) / 2.0f
    };

    for (size_t i = 0; i < 9; i++){
        const Item& item = mInventorySlots[i];
        if (item.getItemType() != AIR){
            item.renderAtPosition({
                // To create a bar
                mPosition.x + mScale.x * i,
                mPosition.y
            });
        }

        // Destination rectangle – centred on gPosition
        Rectangle destinationArea = {
            mPosition.x + mScale.x * i,
            mPosition.y,
            static_cast<float>(mScale.x),
            static_cast<float>(mScale.y)
        };

        if (i != mCurrentSlot){
            // Render the texture on screen
            DrawTexturePro(
                mTexture, 
                textureArea, destinationArea, originOffset,
                0, WHITE
            );
        }
        else{
            DrawTexturePro(
                mTexture, 
                activeSlotTextureArea, destinationArea, originOffset,
                0, WHITE
            );
        }
    }
}