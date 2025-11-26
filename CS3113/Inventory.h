#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include "MonsterManager.h"

class Inventory
{
private:
    Vector2 mPosition;
    Vector2 mScale;
    Texture2D mTexture;
    ItemType mActiveItemType;
    Item mInventorySlots[9];
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

    void redeemMonsterDrops(MonsterManager* monsterManager){
        for (Item * item : monsterManager -> redeemDrops()){
            addItem(item);
        }
        monsterManager->clearDrops();
    }

    void UpdateSlotWithScroll(float scroll){
        mCurrentSlot += static_cast<int>(round(scroll));
        // Ensure it is within bounds
        mCurrentSlot = std::max(0, std::min(mCurrentSlot, 8));
    }

    int sellAll(){
        int sum = 0;
        for (Item & inventorySlot : mInventorySlots){
            if (inventorySlot.getItemType() == SELLABLE){
                sum += inventorySlot.getQuantity();
                inventorySlot.setQuantity(0);
            } 
        }
        return sum;
    }
    
    void setTexture(const char *textureFilepath)
    {   
        UnloadTexture(mTexture);
        mTexture = LoadTexture(textureFilepath);
    }

    void addItem(const Item * item){
        // FIRST CHECK IF THE ITEM EXISTS IN THE INVENTORY, TO ADD QUANTITY IF TRUE
        for (size_t i = 0; i < 9; i++){
            Item & inventorySlot = mInventorySlots[i]; 
            if (inventorySlot.getItemID() == item->getItemID()){
                inventorySlot.addQuantity(1);
                return;
            }
        }

        // Otherwise look for first open slot and claim it :)
        for (size_t j = 0; j < 9; j++){
            Item & inventorySlot = mInventorySlots[j]; 
            if (inventorySlot.getQuantity() <= 0){
                inventorySlot.setToItem(item);
                inventorySlot.setPosition({mPosition.x + mScale.x * j, mPosition.y});    
                break;
            }
        }
    }

    void consumeItemAtSlot(){
        mInventorySlots[mCurrentSlot].addQuantity(-1);
    }
};

#endif // ENTITY_H