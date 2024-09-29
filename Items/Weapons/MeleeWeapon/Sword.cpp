#include "Sword.h"

Sword::Sword() {
    if (!this->weapon_texture.loadFromFile(
            "Resources/images/sprites/entities/player/player_weapons/assets/sword.png")) {
        throw ("ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE");
    };
    this->initVariables();
    this->initAnimationComponent();
    this->initHitboxComponent();
}

Sword::~Sword() = default;

void Sword::update(const sf::Vector2f &position, const float &dt) {
    this->weapon_sprite.setPosition(position + this->offset);
    this->hitboxComponent->update();
    this->updateAnimation(dt);
}

void Sword::render(sf::RenderTarget &target) {
    target.draw(this->weapon_sprite);
    this->hitboxComponent->render(target);
}

void Sword::updateAnimation(const float &dt) {
    this->animationComponent->play("ATTACK", dt);
}

void Sword::initAnimationComponent() {
    this->animationComponent = new AnimationComponent(this->weapon_sprite, this->weapon_texture);
    this->animationComponent->addAnimation("ATTACK", 2.f, 0, 0, 0, 0, this->dimensions.x, this->dimensions.y, false);
}

void Sword::initVariables() {
    this->dimensions = sf::Vector2i(22, 21);
    this->offset = sf::Vector2f(45, 35);
}

void Sword::initHitboxComponent() {
    this->hitboxComponent = new HitboxComponent(this->weapon_sprite, 0, 0, this->dimensions.x,
                                                this->dimensions.y);
}
