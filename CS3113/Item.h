#ifndef ITEM_H
#define ITEM_H

#include "cs3113.h"

enum ItemType {GUN, HOE, CONSUMABLE, AIR};

class Item
{
private:
    Vector2     mScale;
    Texture2D   mTexture;
    ItemType    mItemType;
    int         mQuantity; 

public:
    static constexpr int   DEFAULT_SIZE          = 100;

    Item(ItemType itemType, Vector2 scale, int quantity, const char *textureFilepath);
    Item();
    ~Item();

    void renderAtPosition(Vector2 position) const;

    /*
        ---------- Getters and Setters ---------- 
    */
    int         getQuantity()   const { return mQuantity; }
    Vector2     getScale()      const { return mScale;    }
    ItemType    getItemType()   const { return mItemType; }
    Texture2D   getTexture()    const { return mTexture;  }

    void setScale   (Vector2 scale)     { mScale    = scale;     }
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
    }
};

#endif // ENTITY_H