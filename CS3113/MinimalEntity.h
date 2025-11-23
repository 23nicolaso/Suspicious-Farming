#ifndef MINIMAL_ENTITY_H
#define MINIMAL_ENTITY_H

#include "cs3113.h"

enum VisibilityStatus {VISIBLE, HIDDEN};

class MinimalEntity
{
protected:
    float   mRotation = 0.0f;
    Vector2 mPosition;
    Vector2 mDirection;
    Vector2 mScale;
    Texture2D mTexture;
    VisibilityStatus mVisibilityStatus = HIDDEN;

public:
    const Vector2 ZERO_VECTOR = {0.0f, 0.0f};

    MinimalEntity(Vector2 position, Vector2 direction, Vector2 scale, const char *textureFilepath);
    ~MinimalEntity();

    void render();
    void activate()   { mVisibilityStatus = VISIBLE; }
    void deactivate() { mVisibilityStatus = HIDDEN; }
    virtual void update(float deltaTime) = 0;

    bool isActive() { return mVisibilityStatus == VISIBLE; }
    
    // GETTERS
    Vector2     getScale()              const { return mScale;                 }
    Vector2     getPosition()           const { return mPosition;              }
    Vector2     getDirection()          const { return mDirection;             }
    Texture2D   getTexture()            const { return mTexture;               }
    VisibilityStatus getVisibility()    const { return mVisibilityStatus;      }
    
    // SETTERS
    void setRotation (float   newRotation)   { mRotation = newRotation;   }
    void setDirection(Vector2 newDirection)  { mDirection = newDirection; }
    void setPosition (Vector2 newPosition)   { mPosition = newPosition;   } 
    void setScale    (Vector2 newScale)      { mScale = newScale;         }
    
    void setTexture(const char *textureFilepath)
    {   
        UnloadTexture(mTexture);
        mTexture = LoadTexture(textureFilepath);
    }
};

#endif 