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
    
    void snapPositionToGrid(const Map * map, Vector2 mouseWorld){
        float tileSize = map->getTileSize();
        float leftBound = map->getLeftBoundary();
        float topBound = map->getTopBoundary();

        int gridCol = floor((mouseWorld.x - leftBound) / tileSize);
        int gridRow = floor((mouseWorld.y - topBound) / tileSize);

        if (gridCol < 0) gridCol = 0;
        if (gridCol >= map->getMapColumns()) gridCol = map->getMapColumns() - 1;
        if (gridRow < 0) gridRow = 0;
        if (gridRow >= map->getMapRows()) gridRow = map->getMapRows() - 1;

        float snappedX = leftBound + (gridCol * tileSize) + (tileSize / 2.0f);
        float snappedY = topBound + (gridRow * tileSize) + (tileSize / 2.0f);

        setPosition({snappedX, snappedY});
    }
};

#endif // ENTITY_H