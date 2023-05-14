#include "../framework/amorfos.h"

void amorfos::start() {
    Entity* player = createEntity();
    player->position.x = 64;
    player->position.y = 64;
}

void amorfos::update(float deltaTime) {
}

void amorfos::onButtonPress(int button) {

}

void amorfos::onButtonRelease(int button) {
  
}

void amorfos::onCollision(amorfos::Entity* entity1, amorfos::Entity* entity2) {

}