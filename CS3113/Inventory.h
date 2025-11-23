#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory
{
private:
    Vector2 mPosition;
    Vector2 mScale;
    Texture2D mTexture;
    ItemType mActiveItemType;
    Item mInventorySlots[10];
    int mCurrentSlot = 0;

    Rectangle textureArea = {
        // top-left corner
        0.0f, 0.0f,

        // width and height
        static_cast<float>(mTexture.width / 2),
        static_cast<float>(mTexture.height)
    };
    Rectangle activeSlotTextureArea = {
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


public:
    Inventory(Vector2 position, Vector2 scale, const char *textureFilepath);
    ~Inventory();

    void render();

    Vector2     getPosition()              const { return mPosition;              }
    Texture2D   getTexture()               const { return mTexture;               }

    ItemType    getItemType()              const { return mInventorySlots[mCurrentSlot].getItemType(); }
    int         getCurrentSlotQuantity()   const { return mInventorySlots[mCurrentSlot].getQuantity(); }

    void SetCurrentSlot(int currentSlot)    { mCurrentSlot = currentSlot; }
    void setPosition(Vector2 newPosition)   { mPosition = newPosition; }
    void setScale(Vector2 newScale)         { mScale = newScale; }

    void UpdateSlotWithScroll(float scroll){
        mCurrentSlot += static_cast<int>(round(scroll));
        // Ensure it is within bounds
        mCurrentSlot = std::max(0, std::min(mCurrentSlot, 8));
    }
    
    void setTexture(const char *textureFilepath)
    {   
        UnloadTexture(mTexture);
        mTexture = LoadTexture(textureFilepath);
    }

    void addItem(const Item * item){
        for (Item & inventorySlot : mInventorySlots){
            if (inventorySlot.getQuantity() <= 0){
                inventorySlot.setToItem(item);    
                break;
            }
        }
    }

    void consumeItemAtSlot(){
        mInventorySlots[mCurrentSlot].addQuantity(-1);
    }
};

#endif // ENTITY_H