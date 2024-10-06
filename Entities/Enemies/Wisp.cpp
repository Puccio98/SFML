#include "Wisp.h"

Wisp::Wisp(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet) {
    this->initVariables();
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

void Wisp::initVariables() {
    this->spriteDimension = std::pair(51, 72);
    this->hitboxDimension = std::pair(51, 72);
}
