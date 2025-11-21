#ifndef ENTITY_H
#define ENTITY_H

#include "Map.h"

enum EntityStatus { ACTIVE, INACTIVE                    };
enum EntityType   { PLAYER, BLOCK, NPC, EMPTY           };
enum BasicMovement{ ENTITY_UP, ENTITY_DOWN, ENTITY_LEFT, ENTITY_RIGHT };

class Entity
{
protected:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;

    Vector2 mScale;
    Vector2 mColliderDimensions;
    
    Texture2D mTexture;
    TextureType mTextureType;
    Vector2 mSpriteSheetDimensions;
    
    // int here is the int associated with each enum value
    std::map<int, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    int mAnimState;
    int mFrameSpeed;

    int mCurrentFrameIndex = 0;
    float mAnimationTime = 0.0f;

    int mSpeed;
    float mAngle;

    bool mIsCollidingTop    = false;
    bool mIsCollidingBottom = false;
    bool mIsCollidingRight  = false;
    bool mIsCollidingLeft   = false;

    // For animations which should play through fully (only once) before allowing other animations / actions to play
    bool mIsAnimationBlocking = false; 
    int mLastDirection;

    EntityStatus mEntityStatus = ACTIVE;
    EntityType   mEntityType;

    bool isColliding(Entity *other) const;

    void checkCollisionY(Entity *collidableEntities, int collisionCheckCount);
    void checkCollisionY(Map *map);

    void checkCollisionX(Entity *collidableEntities, int collisionCheckCount);
    void checkCollisionX(Map *map);
    
    void resetColliderFlags() 
    {
        mIsCollidingTop    = false;
        mIsCollidingBottom = false;
        mIsCollidingRight  = false;
        mIsCollidingLeft   = false;
    }

    void animate(float deltaTime);

public:
    static constexpr int    DEFAULT_SIZE          = 250,
                            DEFAULT_SPEED         = 200,
                            DEFAULT_FRAME_SPEED   = 4;
    static constexpr float  Y_COLLISION_THRESHOLD = 0.5f;

    Entity();
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        EntityType entityType);
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, 
        std::map<int, std::vector<int>> animationAtlas, 
        EntityType entityType);
    ~Entity();

    virtual void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount);
    void render() const;
    void normaliseMovement() { Normalise(&mMovement); }

    void activate()   { mEntityStatus  = ACTIVE;   }
    void deactivate() { mEntityStatus  = INACTIVE; }
    void displayCollider();

    bool isActive() { return mEntityStatus == ACTIVE ? true : false; }

    void updateAtlas() { mAnimationIndices = mAnimationAtlas.at(mAnimState); } 

    void moveUp   () { 
        if (mIsAnimationBlocking) return;
        mMovement.y = -1; 
        mAnimState = ENTITY_UP;
    }
    void moveDown () {
        if (mIsAnimationBlocking) return; 
        mMovement.y =  1; 
        mAnimState = ENTITY_DOWN;
    }
    void moveLeft () { 
        if (mIsAnimationBlocking) return;
        mMovement.x = -1; 
        mAnimState = ENTITY_LEFT;
    }
    void moveRight() { 
        if (mIsAnimationBlocking) return;
        mMovement.x =  1; 
        mAnimState = ENTITY_RIGHT;
    }

    void resetMovement() { mMovement = { 0.0f, 0.0f }; }

    Vector2     getPosition()              const { return mPosition;              }
    Vector2     getMovement()              const { return mMovement;              }
    Vector2     getVelocity()              const { return mVelocity;              }
    Vector2     getScale()                 const { return mScale;                 }
    Vector2     getColliderDimensions()    const { return mScale;                 }
    Vector2     getSpriteSheetDimensions() const { return mSpriteSheetDimensions; }
    Texture2D   getTexture()               const { return mTexture;               }
    TextureType getTextureType()           const { return mTextureType;           }
    int         getAnimState()             const { return mAnimState;             }
    int         getFrameSpeed()            const { return mFrameSpeed;            }
    int         getSpeed()                 const { return mSpeed;                 }
    float       getAngle()                 const { return mAngle;                 }
    EntityType  getEntityType()            const { return mEntityType;            }

    bool isCollidingTop()    const { return mIsCollidingTop;    }
    bool isCollidingBottom() const { return mIsCollidingBottom; }

    std::map<int, std::vector<int>> getAnimationAtlas() const { return mAnimationAtlas; }

    void setPosition(Vector2 newPosition)
        { mPosition = newPosition;                 }
    void setMovement(Vector2 newMovement)
        { mMovement = newMovement;                 }
    void setScale(Vector2 newScale)
        { mScale = newScale;                       }
    void setTexture(const char *textureFilepath)
        { mTexture = LoadTexture(textureFilepath); }
    void setColliderDimensions(Vector2 newDimensions) 
        { mColliderDimensions = newDimensions;     }
    void setSpriteSheetDimensions(Vector2 newDimensions) 
        { mSpriteSheetDimensions = newDimensions;  }
    void setSpeed(int newSpeed)
        { mSpeed  = newSpeed;                      }
    void setFrameSpeed(int newSpeed)
        { mFrameSpeed = newSpeed;                  }
    void setAngle(float newAngle) 
        { mAngle = newAngle;                       }
    void setEntityType(EntityType entityType)
        { mEntityType = entityType;                }
    void setAnimState(int newAnimState)
    { 
        mAnimState = newAnimState;
        if (mTextureType == ATLAS) mAnimationIndices = mAnimationAtlas.at(mAnimState);
    }
};

#endif // ENTITY_H