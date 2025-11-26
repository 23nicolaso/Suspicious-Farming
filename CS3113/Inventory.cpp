#include "Inventory.h"

Inventory::Inventory(Vector2 position, Vector2 scale, const char *textureFilepath) : mPosition {position}, mScale {scale}, mTexture {LoadTexture(textureFilepath)} {}

Inventory::~Inventory() { UnloadTexture(mTexture); };

void Inventory::render()
{
    for (size_t i = 0; i < 9; i++){
        const Item& item = mInventorySlots[i];
        if (item.getItemType() != AIR && item.getQuantity() > 0){
            item.render();
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