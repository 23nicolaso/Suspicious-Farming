#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "SimpleEntity.h"

class Crosshair : public SimpleEntity
{
public:
    using SimpleEntity::SimpleEntity;
    void update(float deltaTime) override{
        // Do nothing :D
    }    
};

#endif // ENTITY_H