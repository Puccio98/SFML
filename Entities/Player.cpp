#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture_sheet, Tilemap &map) : map(map) {
    this->initVariables();
    Player::setPosition(x, y);

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
    // Se chiamato senza i dati del movimento li calcola autonomamente assumendo che possa muoversi in quelle direzioni/punti
    MovementData next = this->movementComponent->nextMovementData(dt);

    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Player::update(const MovementData &next, const float &dt) {
    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Player::updateAnimation(const float &dt) {
    if (movementComponent->getState(MOVEMENT_STATES::IDLE))
        animationComponent->play("IDLE", dt);
    else if (movementComponent->getState(MOVEMENT_STATES::MOVING_LEFT)) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
        animationComponent->play("WALK", dt, movementComponent->getVelocityMagnitude() /
                                             movementComponent->getMaxVelocity());
    } else if (movementComponent->getState(MOVEMENT_STATES::MOVING_RIGHT)) {
        sprite.setOrigin(258.f, 0.f);
        sprite.setScale(-1.f, 1.f);
        animationComponent->play("WALK", dt, movementComponent->getVelocityMagnitude() /
                                             movementComponent->getMaxVelocity());
    } else
        animationComponent->play("WALK", dt, movementComponent->getVelocityMagnitude() /
                                             movementComponent->getMaxVelocity());
}

void Player::attack(const float &dt) {
    this->animationComponent->play("ATTACK", dt);
}
