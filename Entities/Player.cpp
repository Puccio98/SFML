#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables(std::pair(70, 80), std::pair<int, int>(30, 25));
    this->setPosition(x, y);

    this->createHitboxComponent(20.f, this->spriteDimension.second - this->hitboxDimension.second,
                                this->hitboxDimension.first, this->hitboxDimension.second);
    this->createMovementComponent(300.f, 3800.f, 1800.f);
    this->createAnimationComponent(texture_sheet);
    this->createAttributeComponent();
    this->createSkillComponent();

    this->animationComponent->addAnimation("IDLE_DOWN", 4.f, 0, 0, 1, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("IDLE_UP", 4.f, 0, 1, 1, 1, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_DOWN", 4.f, 0, 2, 3, 2, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_SIDE_DOWN", 4.f, 0, 3, 3, 3, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_SIDE_UP", 4.f, 0, 4, 3, 4, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("MOVING_UP", 4.f, 0, 5, 3, 5, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation("ATTACK", 4.f, 0, 0, 1, 0, this->spriteDimension.first,
                                           this->spriteDimension.second, false);
}

Player::~Player() {

}

//Initializer Functions

void Player::initVariables(std::pair<int, int> sprite_dimension, std::pair<int, int> hitbox_dimension) {
    this->spriteDimension = sprite_dimension;
    this->hitboxDimension = hitbox_dimension;
    this->invincibilityDuration = 1;
}

bool Player::isInvincible() const {
    return invincibilityClock.getElapsedTime().asSeconds() < invincibilityDuration;
}


void Player::update(const float &dt) {
    // Se chiamato senza i dati del movimento li calcola autonomamente assumendo che possa muoversi in quelle direzioni/punti
    MovementData next = this->movementComponent->nextMovementData(dt);

    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
    this->sword.update(this->hitboxComponent->getPosition(), dt);
}

void Player::update(const MovementData &next, const float &dt) {
    this->movementComponent->update(next);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
    this->sword.update(this->hitboxComponent->getPosition(), dt);
}

void Player::updateAnimation(const float &dt) {
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

void Player::flipAnimation(std::optional<DIRECTIONS> dir) {
    if (dir == std::nullopt) { return; }
    if (dir == DIRECTIONS::RIGHT) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
    }
    if (dir == DIRECTIONS::LEFT) {
        sprite.setOrigin(this->getSize().x, 0.f);
        sprite.setScale(-1.f, 1.f);
    }
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
    if (this->animationComponent->getCurrentAnimationKey() == "ATTACK") {
        this->sword.render(target);
    }
}

void Player::takeDamage() {
    std::cout << "mi son fatto male" << std::endl;
    this->invincibilityClock.restart();
    this->attributeComponent->applyDamage();
}
