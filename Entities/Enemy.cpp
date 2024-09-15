#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();
    this->setPosition(x, y);

    this->createHitboxComponent(0, 0, 17, 24);
    this->createMovementComponent(300.f, 3800.f, 1800.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent();
    this->createSkillComponent();

    this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 17, 24);
//    this->animationComponent->addAnimation("WALK", 2.f, 0, 1, 11, 1, 192, 192);
//    this->animationComponent->addAnimation("ATTACK", 2.f, 0, 2, 13, 2, 192 * 2, 192, false);
}

Enemy::~Enemy() {

}

void Enemy::render(sf::RenderTarget &target) {
    Entity::render(target);
}


void Enemy::update(const float &dt) {
    // Se chiamato senza i dati del movimento li calcola autonomamente assumendo che possa muoversi in quelle direzioni/punti
    MovementData next = this->movementComponent->nextMovementData(dt);

    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Enemy::update(const MovementData &next, const float &dt) {
    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Enemy::updateAnimation(const float &dt) {

}

void Enemy::initVariables() {

}