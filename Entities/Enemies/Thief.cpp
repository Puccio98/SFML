#include "Thief.h"


Thief::Thief(float x, float y, sf::Texture &textureSheet) : Enemy(x, y, textureSheet, std::pair(51, 72),
                                                                  std::pair(51, 72)) {
    Thief::initAnimationComponent();
}

Thief::~Thief() = default;

void Thief::updateAnimation(const float &dt) {
    MovementData md = movementComponent->getMovementData();
    std::string animation;

    if (movementComponent->isState(MOVEMENT_STATES::IDLE)) {
        if (md.facingDirection.second == DIRECTIONS::DOWN) {
            animation = "IDLE_DOWN";
        } else if (md.facingDirection.second == DIRECTIONS::UP) {
            animation = "IDLE_UP";
        }
    } else if (movementComponent->isState(MOVEMENT_STATES::MOVING)) {
        if (md.facingDirection.second == DIRECTIONS::DOWN) {
            animation = "MOVING_DOWN";
            if (md.facingDirection.first != std::nullopt) {
                animation = "MOVING_SIDE_DOWN";
            }

        } else if (md.facingDirection.second == DIRECTIONS::UP) {
            animation = "MOVING_UP";
            if (md.facingDirection.first != std::nullopt) {
                animation = "MOVING_SIDE_UP";
            }
        }
        this->flipAnimation(md.facingDirection.first);
    }
    animationComponent->play(animation, dt);
}

void Thief::flipAnimation(std::optional<DIRECTIONS> dir) {
    if (dir == std::nullopt) { return; }
    if (dir == DIRECTIONS::RIGHT) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
    }
    if (dir == DIRECTIONS::LEFT) {
        sprite.setOrigin(this->getHitboxSize().x, 0.f);
        sprite.setScale(-1.f, 1.f);
    }
}

void Thief::initAnimationComponent() {
    this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 1, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("IDLE_UP", 5.f, 0, 1, 1, 1, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_DOWN", 5.f, 0, 2, 3, 2, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_SIDE_DOWN", 5.f, 0, 3, 3, 3, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_SIDE_UP", 5.f, 0, 4, 3, 4, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_UP", 5.f, 0, 5, 3, 5, this->spriteDimension.first,
                                           this->spriteDimension.second);
}