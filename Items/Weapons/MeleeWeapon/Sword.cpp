#include "Sword.h"
#include "../../../Entities/Components/MovementData.h"

Sword::Sword() {
    if (!this->weapon_texture.loadFromFile(
            "Resources/images/sprites/entities/player/player_weapons/sword/sword_sheet_x2.png")) {
        throw ("ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE");
    };
    this->initVariables();
    this->initAnimationComponent();
    this->initHitboxComponent();
}

Sword::~Sword() = default;

void Sword::update(const sf::Vector2f &position, std::string animation, const float &dt) {
    this->weapon_sprite.setPosition(position + this->offset);
    this->hitboxComponent->update();
    this->updateAnimation(animation, dt);
}

void Sword::render(sf::RenderTarget &target) {
    target.draw(this->weapon_sprite);
    this->hitboxComponent->render(target);
}

void Sword::updateAnimation(std::string animation, const float &dt) {
    this->animationComponent->play(animation, dt);
}

void Sword::initAnimationComponent() {
    this->animationComponent = new AnimationComponent(this->weapon_sprite, this->weapon_texture);
    this->animationComponent->addAnimation("ATTACK_DOWN", 2.f, 0, 0, 7, 0, this->dimensions.x, this->dimensions.y, false);
    this->animationComponent->addAnimation("ATTACK_UP", 2.f, 0, 0, 7, 0, this->dimensions.x, this->dimensions.y, false);
}

void Sword::initVariables() {
    this->dimensions = sf::Vector2i(200, 200);
    this->offset = sf::Vector2f(20, 0);
}

void Sword::initHitboxComponent() {
    this->hitboxComponent = new HitboxComponent(this->weapon_sprite, 0, 0, this->dimensions.x,
                                                this->dimensions.y);
}

void Sword::update(const sf::Vector2f &position, const float &dt) {
}

void Sword::updateAnimation(const float &dt) {
}
