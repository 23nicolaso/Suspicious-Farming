#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "cs3113.h"

enum CrosshairStatus {CROSSHAIR_VISIBLE, CROSSHAIR_HIDDEN};

class Crosshair
{
private:
    Vector2 mPosition;
    Vector2 mScale;
    Texture2D mTexture;
    CrosshairStatus mCrosshairStatus = CROSSHAIR_VISIBLE;

public:
    Crosshair(Vector2 position, Vector2 scale, const char *textureFilepath);
    ~Crosshair();

    void render();

    void activate()   { mCrosshairStatus = CROSSHAIR_VISIBLE; }
    void deactivate() { mCrosshairStatus = CROSSHAIR_HIDDEN ; }

    bool isActive() { return mCrosshairStatus == CROSSHAIR_VISIBLE ? true : false; }

    Vector2     getPosition()              const { return mPosition;              }
    Texture2D   getTexture()               const { return mTexture;               }
    
    void setPosition(Vector2 newPosition)
        { mPosition = newPosition;                 }
    void setScale(Vector2 newScale)
        { mScale = newScale;                       }
    
    void setTexture(const char *textureFilepath)
    {   
        UnloadTexture(mTexture);
        mTexture = LoadTexture(textureFilepath);
    }
    };

#endif // ENTITY_H