#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);

    this->createHitboxComponent(92.f, 70.f, 75.f, 106.f);
    this->createMovementComponent(300.f, 3800.f, 1800.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent();
    this->createSkillComponent();

    this->animationComponent->addAnimation("IDLE_DOWN", 10.f, 0, 0, 1, 0, 51, 72);
    this->animationComponent->addAnimation("IDLE_RIGHT", 10.f, 0, 1, 1, 1, 51, 72);
    this->animationComponent->addAnimation("IDLE_UP", 10.f, 0, 2, 1, 2, 51, 72);
    this->animationComponent->addAnimation("WALK_DOWN", 5.f, 0, 3, 3, 3, 51, 72);
    this->animationComponent->addAnimation("WALK_RIGHT", 5.f, 0, 4, 3, 4, 51, 72);
    this->animationComponent->addAnimation("WALK_UP", 5.f, 0, 5, 3, 5, 51, 72);
    this->animationComponent->addAnimation("ATTACK", 2.f, 0, 2, 13, 2, 51, 72, false);
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
    this->sword.update(this->hitboxComponent->getPosition());
}

void Player::updateAnimation(const float &dt) {
    if (movementComponent->getState(MOVEMENT_STATES::IDLE_DOWN)) {
        animationComponent->play("IDLE_DOWN", dt);
    } else if (movementComponent->getState(MOVEMENT_STATES::IDLE_RIGHT)) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
        animationComponent->play("IDLE_RIGHT", dt);
    } else if (movementComponent->getState(MOVEMENT_STATES::IDLE_UP)) {
        animationComponent->play("IDLE_UP", dt);
    } else if (movementComponent->getState(MOVEMENT_STATES::IDLE_LEFT)) {
        sprite.setOrigin(51.f, 0.f);
        sprite.setScale(-1.f, 1.f);
        animationComponent->play("IDLE_RIGHT", dt);
    } else if (movementComponent->getState(MOVEMENT_STATES::MOVING_LEFT)) {
        sprite.setOrigin(51.f, 0.f);
        sprite.setScale(-1.f, 1.f);
        animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocityMagnitude() /
                                                   movementComponent->getMaxVelocity());
    } else if (movementComponent->getState(MOVEMENT_STATES::MOVING_RIGHT)) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
        animationComponent->play("WALK_RIGHT", dt, movementComponent->getVelocityMagnitude() /
                                                   movementComponent->getMaxVelocity());
    } else if (movementComponent->getState(MOVEMENT_STATES::MOVING_DOWN))
        animationComponent->play("WALK_DOWN", dt, movementComponent->getVelocityMagnitude() /
                                                  movementComponent->getMaxVelocity());
    else if (movementComponent->getState(MOVEMENT_STATES::MOVING_UP))
        animationComponent->play("WALK_UP", dt, movementComponent->getVelocityMagnitude() /
                                                movementComponent->getMaxVelocity());
}

void Player::attack(const float &dt) {
    this->animationComponent->play("ATTACK", dt);
}

float Player::getCurrentHp() {
    return this->getAttributeComponent()->getHp();
}

float Player::getMaxHp() {
    return this->getAttributeComponent()->getHpMax();
}

void Player::render(sf::RenderTarget &target) {
    Entity::render(target);
    this->sword.render(target);
}
