#ifndef CROSSHAIR_H
#define CROSSHAIR_H

#include "NPC.h"
#include <algorithm>

class Crosshair : public Entity
{
private:
    std::vector<int> grownCropTiles = {3, 7, 8, 9};

    // Store the last crop / entity accessed for player use item
    int mLastCrop;
    Vector2 mLastMousePos;
    NPC * mLastNPC;


public:
    using Entity::Entity;
    void updateCrosshair(const Map * secondaryMap, const std::vector<NPC *>& NPCs){
        if (std::find(grownCropTiles.begin(), grownCropTiles.end(), secondaryMap->getTileAt(mPosition)) != grownCropTiles.end()){
            // Crop is a fully grown crop :D
            // Swap to the plus icon to pick up the crop
            mAnimState = 1;
            updateAtlas();
            mLastCrop = secondaryMap->getTileAt(mPosition);
            mLastMousePos = mPosition;
        }
        else if (secondaryMap->getTileAt(mPosition) == 500){ // Magic number for door. Awesome programming. :)
            mAnimState = 3;
            updateAtlas();
        }
        else if (secondaryMap->getTileAt(mPosition) == 10){ // magic number for sell button
            mAnimState = 4;
            updateAtlas();
        }

        else {
            for (NPC * npc : NPCs){
                if (isColliding(npc)){
                    // Show the dialog thang
                    mAnimState = 2; 
                    mLastNPC = npc;
                    updateAtlas();
                    return;
                }
            }
            // By default show animstate 0
            mAnimState = 0;
            updateAtlas();
        }
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

    int getCrosshairState() const { return mAnimState;      }
    int getLastCrop()       const { return mLastCrop;       }
    Vector2 getLastPos()    const { return mLastMousePos;   }
    NPC* getLastNPC()       const { return mLastNPC;        }
};

#endif // ENTITY_H