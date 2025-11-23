#ifndef BULLET_H
#define BULLET_H

#include "MinimalEntity.h"
#include "Monster.h"

class Bullet : public MinimalEntity{
private:
    float mAge = 0;
    Vector2 mColliderDimensions;
public:
    static constexpr float MAX_AGE      = 4.0f,
                           BULLET_SPEED = 500.0f;
    
    Bullet();
    using MinimalEntity::MinimalEntity;
    void update(float deltaTime, std::vector<Monster* >& monsters);
    void update(float deltaTime) override {};

    void setColliderDimensions(Vector2 newColliderDimensions) { mColliderDimensions = newColliderDimensions; }
    void setAge(float age) { mAge = age; }
    float getAge(float age) const { return mAge; }
};

#endif