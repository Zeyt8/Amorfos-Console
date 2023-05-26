#if 1 // Remove this or change it to 1 to use. Also remove the #endif at the bottom of the file.
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
int reloadTicks = 2;
float tickTimer = 1.0f;
int ticksForEnemyVertical = 5;
int ticksForSpawnEnemy = 10;

static void createPlayer() {
    player = createEntity(EntityType::PLAYER, newVector2(0, 0), newVector3(255, 0, 0), true, true, NULL);
    Entity* rightWing = createEntity(EntityType::PLAYER, newVector2(1, 0), newVector3(255, 0, 0), true, true, NULL);
    parent(rightWing, player);
    Entity* leftWing = createEntity(EntityType::PLAYER, newVector2(-1, 0), newVector3(255, 0, 0), true, true, NULL);
    parent(leftWing, player);
    Entity* front = createEntity(EntityType::PLAYER, newVector2(0, 1), newVector3(255, 0, 0), true, true, NULL);
    parent(front, player);
}

void amorfos::start() {
    createPlayer();
    setPosition(player, LCD_WIDTH / 2, LCD_HEIGHT / 2);
    setLED(true, 0);
    setLED(true, 1);
}

static void onTick()
{
    if (needToReload) {
        reloadTicks--;
        if (reloadTicks <= 0) {
            bulletCount = maxBullets;
            reloadTicks = 2;
            needToReload = false;
        }
    }
    ticksForEnemyVertical--;
    for (int i = 0; i < entityCount; i++) {
        if (entities[i]->type == EntityType::ENEMY) {
            entities[i]->position.x += 1;
            if (ticksForEnemyVertical <= 0) {
                entities[i]->position.y -= 1;
                ticksForEnemyVertical = 5;
            }
        }
        else if (entities[i]->type == EntityType::BULLET) {
            entities[i]->position.y += 1;
        }
    }
    ticksForSpawnEnemy--;
    if (ticksForSpawnEnemy <= 0) {
        for (int i = 0; i < 5; i++) {
            createEntity(EntityType::ENEMY, newVector2(i * 3, 0), newVector3(0, 255, 0), true, true, NULL);
        }
    }
}

void amorfos::update(float deltaTime) {
    /*tickTimer -= deltaTime;
    if (tickTimer <= 0) {
        tickTimer = 1.0f;
        onTick();
    }*/
}

void amorfos::onButtonPress(int button) {
    if (button == BUTTON_TOP) {
        if (bulletCount > 0) {
            createEntity(EntityType::BULLET, newVector2(player->position.x, player->position.y), newVector3(255, 255, 0), true, true, NULL);
            bulletCount--;
        }
        else {
            needToReload = true;
        }
    }
}

void amorfos::onButtonRelease(int button) {
  
}

static void gameOver() {
    for (int i = entityCount; i >= 0; i--) {
        destroyEntity(entities[i]);
    }
    start();
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
            gameOver();
        }
    }
    else if (entity1->type == EntityType::BULLET && entity2->type == EntityType::ENEMY) {
        destroyEntity(entity1);
        destroyEntity(entity2);
    }
}

#endif // If you removed the #if 1 at the top of the file, remove this too.