#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);

    this->createHitboxComponent(this->sprite, 92.f, 70.f, 75.f, 106.f);
    this->createMovementComponent(300.f, 1500.f, 600.f);
    this->createAnimationComponent(texture_sheet);

    this->animationComponent->addAnimation("IDLE", 2.f, 0, 0, 13, 0, 192, 192);
    this->animationComponent->addAnimation("WALK", 2.f, 0, 1, 11, 1, 192, 192);
    this->animationComponent->addAnimation("ATTACK", 2.f, 0, 2, 13, 2, 192 * 2, 192, false);
}

Player::~Player() {

}

//Initializer Functions

void Player::initVariables() {

}

void Player::update(const float &dt) {
    MovementData next = this->movementComponent->nextMovementData(dt);
    // if next is allowed
    if (true) {
        this->movementComponent->update(next);
    }

    if (this->movementComponent->getState(MOVEMENT_STATES::IDLE))
        this->animationComponent->play("IDLE", dt);
    else if (this->movementComponent->getState(MOVEMENT_STATES::MOVING_LEFT)) {
        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocityMagnitude() /
                                                   this->movementComponent->getMaxVelocity());
    } else if (this->movementComponent->getState(MOVEMENT_STATES::MOVING_RIGHT)) {
        this->sprite.setOrigin(258.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocityMagnitude() /
                                                   this->movementComponent->getMaxVelocity());
    } else
        this->animationComponent->play("WALK", dt, this->movementComponent->getVelocityMagnitude() /
                                                   this->movementComponent->getMaxVelocity());

    this->hitboxComponent->update();
}

void Player::attack(const float &dt) {
    this->animationComponent->play("ATTACK", dt);
}
