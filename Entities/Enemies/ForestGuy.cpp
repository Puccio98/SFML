#include "ForestGuy.h"


ForestGuy::ForestGuy(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet) {
    ForestGuy::initAnimationComponent();
}

ForestGuy::~ForestGuy() = default;

void ForestGuy::updateAnimation(const float &dt) {
    // Play the idle animation
    this->animationComponent->play("IDLE_DOWN", dt);
}

void ForestGuy::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 1, 0, 51, 72);
}
