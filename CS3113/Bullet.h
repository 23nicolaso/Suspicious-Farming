#ifndef BULLET_H
#define BULLET_H

#include "SimpleEntity.h"

class Bullet : public SimpleEntity{
private:
    float mAge = 0;
public:
    static constexpr float MAX_AGE      = 4.0f,
                           BULLET_SPEED = 500.0f;
    
    Bullet();
    using SimpleEntity::SimpleEntity;
    void update(float deltaTime) override;

    void setAge(float age) { mAge = age; }
    float getAge(float age) const { return mAge; }
};

#endif