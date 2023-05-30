#if 1 // Remove this or change it to 1 to use. Also remove the #endif at the bottom of the file.
// This is needed because there are multiple game projects in the repo and they are all implementing the functions from amorfos.h.

#include "../../framework/amorfos.h"
#include <stdint.h>

using namespace amorfos;

enum EntityType {
    PLAYER,
    ENEMY,
    BULLET,
    NOTHING
};

Entity* player;
uint8_t playerHealth = 2;
uint8_t maxBullets = 3;
uint8_t bulletCount = 3;
bool needToReload = false;
int reloadTicks = 2;
float tickTimer = 1.0f;
int ticksForEnemyVertical = 7;
int ticksForSpawnEnemy = 2;
int enemyDir = 1;

static void createPlayer() {
    player = createEntity(EntityType::PLAYER, newVector2(0, 0), newVector3(255, 0, 0), true, true, NULL);
    uint16_t graphics[3][3] = {
        { 0, 1, 0 },
        { 1, 1, 1 },
        { 0, 0, 0 }
    };
    setGraphics(player, graphics);
    setCollisionRadius(player, 1);
}

static void createEnemy(int x, int y) {
    Entity* enemy = createEntity(EntityType::ENEMY, newVector2(x, y), newVector3(0, 255, 0), true, true, NULL);
    uint16_t graphics[3][3] = {
        { 1, 0, 1 },
        { 0, 1, 0 },
        { 1, 0, 1 }
    };
    setGraphics(enemy, graphics);
    setCollisionRadius(enemy, 1);
}

static void createBullet(int x, int y) {
    Entity* bullet = createEntity(EntityType::BULLET, newVector2(x, y), newVector3(255, 255, 0), true, true, NULL);
    uint16_t graphics[3][3] = {
        { 0, 0, 0 },
        { 0, 1, 0 },
        { 0, 1, 0 }
    };
    setGraphics(bullet, graphics);
    setCollisionRadius(bullet, 0);
}

void amorfos::start() {
    createPlayer();
    setPosition(player, LCD_WIDTH / 2, LCD_HEIGHT / 2 - 10);
    setLED(true, LED0);
    setLED(true, LED1);
    renderUpdateFrequency = 1.0f;
}

static void onTick()
{
    // reload
    if (needToReload) {
        reloadTicks--;
        if (reloadTicks <= 0) {
            bulletCount = maxBullets;
            reloadTicks = 2;
            needToReload = false;
        }
    }
    // entity movement
    ticksForEnemyVertical--;
    for (int i = 0; i < entityCount; i++) {
        if (entities[i]->type == EntityType::ENEMY) {
            move(entities[i], 5 * enemyDir, 0);
            if (ticksForEnemyVertical <= 0) {
                move(entities[i], 0, -10);
            }
        }
        else if (entities[i]->type == EntityType::BULLET) {
            move(entities[i], 0, 2);
        }
        else if (entities[i]->type == EntityType::PLAYER) {
            move(entities[i], input.joystickX * 5, input.joystickY * 5);
        }   
    }
    if (ticksForEnemyVertical <= 0) {
        ticksForEnemyVertical = 7;
        enemyDir *= -1;
    }
    // enemy ocasionally spawns
    ticksForSpawnEnemy--;
    if (ticksForSpawnEnemy <= 0) {
        ticksForSpawnEnemy = 22;
        for (int i = (LCD_WIDTH / 2) - 12; i < (LCD_WIDTH / 2) + 13; i += 5) {
            createEnemy(i, LCD_HEIGHT - 10);
        }
    }
}

void amorfos::update(float deltaTime) {
    tickTimer -= deltaTime;
    if (tickTimer <= 0) {
        tickTimer = 1.0f;
        onTick();
    }
}

void amorfos::onButtonPress(int button) {
    if (button == BUTTON_TOP) {
        if (bulletCount > 0) {
            createBullet(player->position.x, player->position.y);
            bulletCount--;
            playSound(1100, 300);
        }
        else {
            needToReload = true;
        }
    }
}

void amorfos::onButtonRelease(int button) {
}

static void gameOver() {
    restart();
}

void amorfos::onCollision(amorfos::Entity* entity1, amorfos::Entity* entity2) {
    if (entity1->type == EntityType::PLAYER && entity2->type == EntityType::ENEMY) {
        playerHealth--;
        playSound(600, 600);
        if (playerHealth == 1) {
            setLED(false, LED1);
        }
        else if (playerHealth == 0) {
            setLED(false, LED0);
            // game over
            gameOver();
        }
        destroyEntity(entity2);
    }
    else if (entity1->type == EntityType::BULLET && entity2->type == EntityType::ENEMY) {
        destroyEntity(entity1);
        destroyEntity(entity2);
    }
}

#endif // If you removed the #if 1 at the top of the file, remove this too.