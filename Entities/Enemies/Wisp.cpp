#include "Wisp.h"

Wisp::Wisp(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet, std::pair(51, 72),
                                                                std::pair(51, 72)) {
    Wisp::initAnimationComponent();
}

Wisp::~Wisp() = default;

void Wisp::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE", 5.f, 0, 0, 3, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
}

void Wisp::updateAnimation(const float &dt) {
    // Play the idle animation
    this->animationComponent->play("IDLE", dt);
}
