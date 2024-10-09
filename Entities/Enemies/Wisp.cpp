#include "Wisp.h"

Wisp::Wisp(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet, std::pair(64, 64),
                                                                std::pair(64, 64)) {
    Wisp::initAnimationComponent();
}

Wisp::~Wisp() = default;

void Wisp::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE", 5.f, 0, 0, 4, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
}

void Wisp::updateAnimation(const float &dt) {
    // Play the idle animation
    this->animationComponent->play("IDLE", dt);
}
