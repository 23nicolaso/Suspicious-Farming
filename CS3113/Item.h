#ifndef ITEM_H
#define ITEM_H

#include "cs3113.h"

enum ItemType {GUN, HOE, CONSUMABLE, SELLABLE, AIR};
enum ItemID   {GUN_ITEM, HOE_ITEM, PEANUT_DROP, PEANUT_SEED, RADDISH_DROP, CRABWEED_DROP, CLOVER_DROP, AIR_ITEM};

class Item
{
private:
    Vector2     mScale;
    Vector2     mPosition;
    
    Texture2D   mTexture;
    ItemType    mItemType;
    ItemID      mItemID;
    int         mQuantity; 

public:
    static constexpr int DEFAULT_SIZE = 100;

    Item(ItemType itemType, ItemID itemID, Vector2 scale, int quantity, const char *textureFilepath);
    Item();
    ~Item();

    void render() const;

    /*
        ---------- Getters and Setters ---------- 
    */
    int         getQuantity()   const { return mQuantity; }
    Vector2     getScale()      const { return mScale;    }
    ItemType    getItemType()   const { return mItemType; }
    ItemID      getItemID()     const { return mItemID;   }    
    Texture2D   getTexture()    const { return mTexture;  }
    Vector2     getPosition()   const { return mPosition; }

    void setScale   (Vector2 scale)     { mScale    = scale;     }
    void setPosition(Vector2 position)  { mPosition = position;  }
    void setQuantity(int quantity)      { mQuantity = quantity;  }
    void setItemtype(ItemType itemType) { mItemType = itemType;  }
    void addQuantity(int quantity)      { mQuantity += quantity; } 

    void setTexture (const char *textureFilepath)
    {   
        UnloadTexture(mTexture);
        mTexture = LoadTexture(textureFilepath);
    }

    void setToItem  (const Item *item){
        mScale    = item -> mScale;
        mTexture  = item -> mTexture;
        mItemType = item -> mItemType;
        mQuantity = item -> mQuantity;
        mItemID   = item -> mItemID;
    }
};

#endif // ENTITY_H