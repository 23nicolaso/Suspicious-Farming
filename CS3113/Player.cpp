#include "Player.h"

const std::map<int, std::vector<int>> Player::playerAnimationAtlas = {
    {RIGHT_SLASH,  { 25, 26, 27, 28, 29 }},
    {LEFT_SLASH,   { 30, 31, 32, 33, 34 }},
    {DOWN,         { 1,  0,  1,  2  }},
    {LEFT,         { 10, 9,  10, 11 }},
    {UP,           { 4,  3,  4,  5  }},
    {RIGHT,        { 7,  6,  7,  8  }},
    {UP_HOLDING,   { 12, 13, 14, 13 }},
    {LEFT_HOLDING, { 18, 19, 20, 19 }},
    {RIGHT_HOLDING,{ 15, 16, 17, 16 }},
    {DOWN_HOLDING, { 40, 39, 40, 41 }},
    {DOWN_SLASH,   { 21, 22, 23, 24 }},
    {UP_SLASH,     { 35, 36, 37, 38 }},
    {DOWN_GUN,     { 42, 43, 44, 43 }},
    {RIGHT_GUN,    { 45, 46, 47, 46 }},
    {UP_GUN,       { 51, 52, 53, 52 }},
    {LEFT_GUN,     { 48, 49, 50, 49 }},
    {LEFT_SHOOT,   { 49, 55, 49 }},
    {RIGHT_SHOOT,  { 46, 54, 46 }},
    {UP_SHOOT,     { 52, 57, 52 }},
    {DOWN_SHOOT,   { 43, 56, 43 }}
};

void Player::useItem(MonsterManager * monsterManager, BulletManager * bulletManager, Map * map, Map * plantMap, Inventory * inventory, ItemType activeItemType, Crosshair * crosshair, DialogueHandler * dialogueHandler, Vector2 mousePosition){
    if(crosshair -> getCrosshairState() != 0){
        if (crosshair -> getCrosshairState() == 1){ // FULLY GROWN CROP
            plantMap->setTileAt(crosshair -> getLastPos(), 0); // Return to unhoed dirt 
            if (crosshair -> getLastCrop() == 3){
                // Summon a peanut for the player to kill at position
                monsterManager -> spawnMonster(PEANUT, crosshair->getLastPos());
            }
            else if (crosshair -> getLastCrop() == 7){
                // Give player clover item
                inventory->addItem(
                    new Item(
                        SELLABLE,
                        CLOVER_DROP,
                        {ITEM_SCALE, ITEM_SCALE},
                        1,
                        "assets/game/cloveritem.png"
                    )
                );
            }
            else if (crosshair -> getLastCrop() == 8){
                // Summon a radish
                monsterManager -> spawnMonster(RADDISH, crosshair->getLastPos());
            }
            else if (crosshair -> getLastCrop() == 9){
                // Summon a crab
                monsterManager -> spawnMonster(CRABWEED, crosshair->getLastPos());
            }
        }
        else if (crosshair -> getCrosshairState() == 2){ // NPC DIALOG
            dialogueHandler->setDialogueLines(crosshair -> getLastNPC()->getDialogLines());
            dialogueHandler->activate();
        }
    }
    else{
        if (activeItemType == HOE){
            if (mIsAnimationBlocking){
                // Can't double block!
                return;
            }

            // HANDLE AUDIO
            PlaySound(slashSound);

            // HANDLE ANIMATION
            mCurrentFrameIndex = 0;
            mIsAnimationBlocking = true;
            if (abs(mousePosition.x) > 
                abs(mousePosition.y))
            {
                if (mousePosition.x > 0) mAnimState = RIGHT_SLASH;
                else                     mAnimState = LEFT_SLASH;
            } else {
                if (mousePosition.y > 0) mAnimState = DOWN_SLASH;
                else                     mAnimState = UP_SLASH;
            }

            // CORRECT MOUSE POSITION FOR WORLD
            mousePosition.x += mPosition.x;
            mousePosition.y += mPosition.y;

            // HANDLE MAP ADJUSTMENT
            if ((map->getTileAt(mousePosition) == 4 || map->getTileAt(mousePosition) == 5 || map->getTileAt(mousePosition) == 6) && Vector2Distance(mousePosition, mPosition) < 150.0f) {
                map->setTileAt(mousePosition, 7);
            }
        }

        else if (activeItemType == GUN){
            if (mIsAnimationBlocking){
                // Can't double block!
                return;
            }

            // HANDLE AUDIO
            PlaySound(shootSound);

            mCurrentFrameIndex = 0;
            mIsAnimationBlocking = true;
            if (abs(mousePosition.x) > 
                abs(mousePosition.y))
            {
                if (mousePosition.x > 0) {
                    mAnimState = RIGHT_SHOOT;
                    bulletManager -> shoot(
                        {1.0f, 0.0f}, 
                        {mPosition.x + BULLET_SPAWN_OFFSET, mPosition.y}
                    );
                }
                else {
                    mAnimState = LEFT_SHOOT;
                    bulletManager -> shoot(
                        {-1.0f, 0.0f}, 
                        {mPosition.x - BULLET_SPAWN_OFFSET, mPosition.y}
                    );
                }
            } else {
                if (mousePosition.y > 0) {
                    mAnimState = DOWN_SHOOT;
                    bulletManager -> shoot(
                        {0.0f, 1.0f}, 
                        {mPosition.x, mPosition.y + BULLET_SPAWN_OFFSET}
                    );
                }
                else {
                    mAnimState = UP_SHOOT;
                    bulletManager -> shoot(
                        {0.0f, -1.0f}, 
                        {mPosition.x, mPosition.y - BULLET_SPAWN_OFFSET}
                    );
                }
            }
        }

        else if (activeItemType == CONSUMABLE){
            if (inventory -> getCurrentSlotQuantity() <= 0){
                return;
            }

            // CORRECT MOUSE POSITION FOR WORLD
            mousePosition.x += mPosition.x;
            mousePosition.y += mPosition.y;

            // Check if land is farmland and there isn't a crop there already!
            if (map -> getTileAt(mousePosition) == 7 && plantMap -> getTileAt(mousePosition) == 0){ 
                inventory -> consumeItemAtSlot();
                // HANDLE AUDIO
                PlaySound(plantSound);

                // will be more sophisticated in future, but for now just put the peanut seeds if possible!
                plantMap->setTileAt(mousePosition, 1);
            }
        }
    }
}

void Player::lookAtMouse(ItemType activeItemType, Vector2 mousePosition)
{
    if (mIsAnimationBlocking) return;

    if (activeItemType == GUN){
        if (abs(mousePosition.x) > 
            abs(mousePosition.y))
        {
            if (mousePosition.x > 0) mAnimState = RIGHT_GUN;
            else                     mAnimState = LEFT_GUN;
        } else {
            if (mousePosition.y > 0) mAnimState = DOWN_GUN;
            else                     mAnimState = UP_GUN;
        }
    }
    else {
        return;
    }
}