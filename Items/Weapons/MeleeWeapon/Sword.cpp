#include "Sword.h"

Sword::Sword() {
    if (!this->weapon_texture.loadFromFile("Resources/images/sprites/entities/player/player_weapons/spada.png")) {
        throw ("ERROR::PLAYER::COULD NOT LOAD WEAPON TEXTURE");
    };
    this->weapon_sprite.setTexture(weapon_texture);
}

Sword::~Sword() {

}

void Sword::update(const sf::Vector2f &position) {
    this->weapon_sprite.setPosition(position);
}

void Sword::render(sf::RenderTarget &target) {
    target.draw(this->weapon_sprite);
}
