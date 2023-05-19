#if 1 //Remove this or change it to 1 to use. Also remove the #endif at the bottom of the file.
// This is needed because there are multiple game projects in the repo and they are all implementing the functions from amorfos.h.

#include "../../framework/amorfos.h"
#include <stdint.h>

using namespace amorfos;

enum EntityType {
    PLAYER,
    ENEMY,
    BULLET
};

Entity* player;
uint8_t playerHealth = 2;
uint8_t maxBullets = 3;
uint8_t bulletCount = 0;
bool needToReload = false;
float reloadTime = 1.0f;

void amorfos::start() {
    player = createEntity(EntityType::PLAYER, newVector2(0, 0), newVector3(1, 0, 0), true, true, NULL);
    setLED(true, 0);
    setLED(true, 1);
}

void amorfos::update(float deltaTime) {
    if (needToReload) {
        reloadTime -= deltaTime;
        if (reloadTime <= 0) {
            bulletCount = maxBullets;
            reloadTime = 1.0f;
            needToReload = false;
        }
    }
}

void amorfos::onButtonPress(int button) {
    if (button == BUTTON_TOP) {
        if (bulletCount > 0) {
            createEntity(EntityType::BULLET, newVector2(player->position.x, player->position.y), newVector3(1, 1, 0), true, true, NULL);
            bulletCount--;
        }
        else {
            needToReload = true;
        }
    }
}

void amorfos::onButtonRelease(int button) {
  
}

void amorfos::onCollision(amorfos::Entity* entity1, amorfos::Entity* entity2) {
    if (entity1->type == EntityType::PLAYER && entity2->type == EntityType::ENEMY) {
        playerHealth--;
        if (playerHealth == 0) {
            destroyEntity(player);
            if (playerHealth == 1) {
                setLED(false, LED1);
            }
            else if (playerHealth == 0) {
                setLED(false, LED0);
            }
            // game over
        }
    }
    else if (entity1->type == EntityType::BULLET && entity2->type == EntityType::ENEMY) {
        destroyEntity(entity1);
        destroyEntity(entity2);
    }
}

#endif // Also remove this to use