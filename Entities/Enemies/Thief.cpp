#include "Thief.h"


Thief::Thief(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet) {
    Thief::initAnimationComponent();
}

Thief::~Thief() = default;

void Thief::updateAnimation(const float &dt) {
    // Play the idle animation
    this->animationComponent->play("IDLE_DOWN", dt);
}

void Thief::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 1, 0, 51, 72);
}
