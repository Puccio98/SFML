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

    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::IDLE_DOWN), 5.f, 0, 0, 1, 0, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::IDLE_UP), 5.f, 0, 1, 1, 1, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::MOVING_DOWN), 4.f, 0, 2, 3, 2, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::MOVING_SIDE_DOWN), 4.f, 0, 3, 3, 3, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::MOVING_SIDE_UP), 4.f, 0, 4, 3, 4, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::MOVING_UP), 4.f, 0, 5, 3, 5, this->spriteDimension.first,
                                           this->spriteDimension.second);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::ATTACK_DOWN), 2.f, 0, 6, 7, 6, this->spriteDimension.first,
                                           this->spriteDimension.second, false);
    this->animationComponent->addAnimation(getAnimationKey(PLAYER_ANIMATIONS::ATTACK_UP), 2.f, 0, 7, 7, 7, this->spriteDimension.first,
                                           this->spriteDimension.second, false);
}

Player::~Player() {

}

//Initializer Functions

void Player::initVariables(std::pair<int, int> sprite_dimension, std::pair<int, int> hitbox_dimension) {
    this->spriteDimension = sprite_dimension;
    this->hitboxDimension = hitbox_dimension;
    this->invincibilityDuration = 1;
    this->nextAnimation = PLAYER_ANIMATIONS::IDLE_DOWN;
}

bool Player::isInvincible() const {
    return invincibilityClock.getElapsedTime().asSeconds() < invincibilityDuration;
}

void Player::update(const float &dt) {
    // Se chiamato senza i dati del movimento li calcola autonomamente assumendo che possa muoversi in quelle direzioni/punti
    MovementData next = this->movementComponent->nextMovementData(dt);

    this->movementComponent->update(next);
    this->updateCurrentAnimation(dt);
    animationComponent->play(getAnimationKey(this->nextAnimation), dt);

    this->hitboxComponent->update();
    if (this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_DOWN) || this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_UP) ) {
        this->sword.update(this->hitboxComponent->getPosition(), this->animationComponent->getCurrentAnimation(), dt);
    }}

void Player::update(const MovementData &next, const float &dt) {
    this->movementComponent->update(next);
    this->updateCurrentAnimation(dt);
    animationComponent->play(getAnimationKey(this->nextAnimation), dt);

    this->hitboxComponent->update();
    if (this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_DOWN) || this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_UP) ) {
        this->sword.update(this->hitboxComponent->getPosition(), getAnimationKey(this->nextAnimation), dt);
    }
}

void Player::updateCurrentAnimation(const float &dt) {
    MovementData md = movementComponent->getMovementData();

    if (movementComponent->isState(MOVEMENT_STATES::IDLE)) {
        if (md.facingDirection.second == DIRECTIONS::DOWN) {
            this->nextAnimation = PLAYER_ANIMATIONS::IDLE_DOWN;
        } else if (md.facingDirection.second == DIRECTIONS::UP) {
            this->nextAnimation = PLAYER_ANIMATIONS::IDLE_UP;
        }
    } else if (movementComponent->isState(MOVEMENT_STATES::MOVING)) {
        if (md.facingDirection.second == DIRECTIONS::DOWN) {
            this->nextAnimation = PLAYER_ANIMATIONS::MOVING_DOWN;
            if (md.facingDirection.first != std::nullopt) {
                this->nextAnimation = PLAYER_ANIMATIONS::MOVING_SIDE_DOWN;
            }
        } else if (md.facingDirection.second == DIRECTIONS::UP) {
            this->nextAnimation = PLAYER_ANIMATIONS::MOVING_UP;
            if (md.facingDirection.first != std::nullopt) {
                this->nextAnimation = PLAYER_ANIMATIONS::MOVING_SIDE_UP;
            }
        }
        this->flipAnimation(md.facingDirection.first);
    } else if (md.facingDirection.second == DIRECTIONS::DOWN) {
        this->animationComponent->play(getAnimationKey(PLAYER_ANIMATIONS::ATTACK_DOWN), dt);
    } else if (md.facingDirection.second == DIRECTIONS::UP) {
        this->animationComponent->play(getAnimationKey(PLAYER_ANIMATIONS::ATTACK_UP), dt);
    }
}

void Player::flipAnimation(std::optional<DIRECTIONS> dir) {
    if (dir == std::nullopt) { return; }
    if (dir == DIRECTIONS::RIGHT) {
        sprite.setOrigin(0.f, 0.f);
        sprite.setScale(1.f, 1.f);
    }
    if (dir == DIRECTIONS::LEFT) {
        sprite.setOrigin(this->getSpriteSize().x, 0.f);
        sprite.setScale(-1.f, 1.f);
    }
}

void Player::attack(const float &dt) {
    MovementData md = movementComponent->getMovementData();
    this->nextAnimation = md.facingDirection.second == DIRECTIONS::DOWN ? PLAYER_ANIMATIONS::ATTACK_DOWN : PLAYER_ANIMATIONS::ATTACK_UP;
    this->animationComponent->play(getAnimationKey(nextAnimation), dt);
}

float Player::getCurrentHp() {
    return this->getAttributeComponent()->getHp();
}

float Player::getMaxHp() {
    return this->getAttributeComponent()->getHpMax();
}

void Player::render(sf::RenderTarget &target) {
    Entity::render(target);
    if (this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_DOWN) || this->animationComponent->getCurrentAnimation() == this->getAnimationKey(PLAYER_ANIMATIONS::ATTACK_UP) ) {
        this->sword.render(target);
    }
}

void Player::takeDamage() {
    this->invincibilityClock.restart();
    this->attributeComponent->applyDamage();
}

std::string Player::getAnimationKey(PLAYER_ANIMATIONS animation) {
    switch (animation) {
        case PLAYER_ANIMATIONS::IDLE_DOWN: return "IDLE_DOWN";
        case PLAYER_ANIMATIONS::IDLE_UP: return "IDLE_UP";
        case PLAYER_ANIMATIONS::MOVING_DOWN: return "MOVING_DOWN";
        case PLAYER_ANIMATIONS::MOVING_SIDE_DOWN: return "MOVING_SIDE_DOWN";
        case PLAYER_ANIMATIONS::MOVING_SIDE_UP: return "MOVING_SIDE_UP";
        case PLAYER_ANIMATIONS::MOVING_UP: return "MOVING_UP";
        case PLAYER_ANIMATIONS::ATTACK_DOWN: return "ATTACK_DOWN";
        case PLAYER_ANIMATIONS::ATTACK_UP: return "ATTACK_UP";
        default:
            return "UNKNOWN";
    }
}
