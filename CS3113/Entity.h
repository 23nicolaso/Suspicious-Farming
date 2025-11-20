#ifndef ENTITY_H
#define ENTITY_H

#include "Map.h"
#include "Item.h"
#include "BulletManager.h"

enum AnimState    { 
    LEFT, UP, RIGHT, DOWN, UP_HOLDING, RIGHT_HOLDING, LEFT_HOLDING, 
    DOWN_SLASH, RIGHT_SLASH, UP_SLASH, DOWN_HOLDING, DOWN_GUN, LEFT_GUN,
    LEFT_SLASH, RIGHT_GUN, UP_GUN, LEFT_SHOOT, RIGHT_SHOOT, DOWN_SHOOT, UP_SHOOT              
}; 

enum EntityStatus { ACTIVE, INACTIVE                    };
enum EntityType   { PLAYER, BLOCK, PLATFORM, NPC, EMPTY };
enum AIType       { WANDERER, FOLLOWER                  };
enum AIState      { WALKING, IDLE, FOLLOWING            };

class Entity
{
private:
    Vector2 mPosition;
    Vector2 mMovement;
    Vector2 mVelocity;

    Vector2 mScale;
    Vector2 mColliderDimensions;
    
    Texture2D mTexture;
    TextureType mTextureType;
    Vector2 mSpriteSheetDimensions;
    
    std::map<AnimState, std::vector<int>> mAnimationAtlas;
    std::vector<int> mAnimationIndices;
    AnimState mAnimState;
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
    AnimState mLastDirection;

    EntityStatus mEntityStatus = ACTIVE;
    EntityType   mEntityType;

    AIType  mAIType;
    AIState mAIState;

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
    void AIActivate(Entity *target);
    void AIWander();
    void AIFollow(Entity *target);

public:
    static constexpr int    DEFAULT_SIZE          = 250,
                            DEFAULT_SPEED         = 200,
                            DEFAULT_FRAME_SPEED   = 3;
    static constexpr float  Y_COLLISION_THRESHOLD = 0.5f,
                            BULLET_SPAWN_OFFSET   = 50.0f;

    Entity();
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        EntityType entityType);
    Entity(Vector2 position, Vector2 scale, const char *textureFilepath, 
        TextureType textureType, Vector2 spriteSheetDimensions, 
        std::map<AnimState, std::vector<int>> animationAtlas, 
        EntityType entityType);
    ~Entity();

    void update(float deltaTime, Entity *player, Map *map, 
        Entity *collidableEntities, int collisionCheckCount);
    void render();
    void normaliseMovement() { Normalise(&mMovement); }

    void activate()   { mEntityStatus  = ACTIVE;   }
    void deactivate() { mEntityStatus  = INACTIVE; }
    void displayCollider();

    bool isActive() { return mEntityStatus == ACTIVE ? true : false; }

    void updateAtlas() { mAnimationIndices = mAnimationAtlas.at(mAnimState); } 

    void moveUp    (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.y = -1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = UP;
        else if (heldItem == CONSUMABLE)            mAnimState = UP_HOLDING;
    }
    void moveDown  (ItemType heldItem) {
        if (mIsAnimationBlocking) return; 
        mMovement.y =  1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = DOWN;
        else if (heldItem == CONSUMABLE)            mAnimState = DOWN_HOLDING;
    }
    void moveLeft  (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x = -1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = LEFT;
        else if (heldItem == CONSUMABLE)            mAnimState = LEFT_HOLDING;
    }
    void moveRight (ItemType heldItem) { 
        if (mIsAnimationBlocking) return;
        mMovement.x =  1; 
        if (heldItem == AIR || heldItem == HOE)     mAnimState = RIGHT;
        else if (heldItem == CONSUMABLE)            mAnimState = RIGHT_HOLDING;
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
    AnimState   getAnimState()             const { return mAnimState;             }
    int         getFrameSpeed()            const { return mFrameSpeed;            }
    int         getSpeed()                 const { return mSpeed;                 }
    float       getAngle()                 const { return mAngle;                 }
    EntityType  getEntityType()            const { return mEntityType;            }
    AIType      getAIType()                const { return mAIType;                }
    AIState     getAIState()               const { return mAIState;               }

    
    bool isCollidingTop()    const { return mIsCollidingTop;    }
    bool isCollidingBottom() const { return mIsCollidingBottom; }

    std::map<AnimState, std::vector<int>> getAnimationAtlas() const { return mAnimationAtlas; }

    void lookAtMouse(ItemType activeItemType, Vector2 mousePosition);
    void useItem(BulletManager* bulletManager, ItemType activeItemType, Vector2 mousePosition);

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
    void setAnimState(AnimState newAnimState)
    { 
        mAnimState = newAnimState;
        if (mTextureType == ATLAS) mAnimationIndices = mAnimationAtlas.at(mAnimState);
    }
    void setAIState(AIState newState)
        { mAIState = newState;                     }
    void setAIType(AIType newType)
        { mAIType = newType;                       }
};

#endif // ENTITY_H