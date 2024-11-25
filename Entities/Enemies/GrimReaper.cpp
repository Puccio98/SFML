#include "GrimReaper.h"

GrimReaper::GrimReaper(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet, std::pair(180, 180),
                                                                            std::pair(64, 64)) {
    GrimReaper::initAnimationComponent();
}

GrimReaper::~GrimReaper() = default;

void GrimReaper::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE", 30.f, 0, 0, 4, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING", 30.f, 0, 0, 3, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
}

void GrimReaper::updateAnimation(const float &dt) {
    MovementData md = movementComponent->getMovementData();
    std::string animation;

    if (movementComponent->isState(MOVEMENT_STATES::IDLE)) {
        animation = "IDLE";
    }else if (movementComponent->isState(MOVEMENT_STATES::MOVING)) {
        animation = "MOVING";
    }

    this->flipAnimation(md.facingDirection.first);
    animationComponent->play(animation, dt);
}
