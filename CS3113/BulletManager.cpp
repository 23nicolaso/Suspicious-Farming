#include "BulletManager.h"

void BulletManager::shoot(Vector2 direction, Vector2 spawnPosition){
    // Find first unallocated bullet
    for (Bullet& bullet: bullets){
        if (bullet.getVisibility() == HIDDEN){
            bullet.setDirection(direction);
            
            // Set Rotation based on direction vector.
            bullet.setRotation(atan2(direction.y, direction.x)*180.0f/PI);

            bullet.setPosition(spawnPosition);
            bullet.setAge(0.0f);
            bullet.activate();
            return;
        }
    }
}

void BulletManager::update(float deltaTime){
   for (Bullet& bullet : bullets){
        bullet.update(deltaTime);
   }
}

void BulletManager::render(){
    for (Bullet& bullet : bullets){
        bullet.render();
    }
}