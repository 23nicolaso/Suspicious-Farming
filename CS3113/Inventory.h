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
    int mLastOpenSlot = 0;
    int mCurrentSlot = 0;

public:
    Inventory(Vector2 position, Vector2 scale, const char *textureFilepath);
    ~Inventory();

    void render();

    bool        getInventoryFull()         const { return mLastOpenSlot > 9;      }
    Vector2     getPosition()              const { return mPosition;              }
    Texture2D   getTexture()               const { return mTexture;               }

    ItemType    getItemType()              const { return mInventorySlots[mCurrentSlot].getItemType(); }

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
        if (mLastOpenSlot < 9){
            mInventorySlots[mLastOpenSlot].setToItem(item);
            mLastOpenSlot += 1;
        }
    }
};

#endif // ENTITY_H