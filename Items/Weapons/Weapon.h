#pragma once

#include "../Item.h"
#include "../../Entities/Entity.h"

class Weapon : public Item {
private:
    void updateAnimation(const float &dt) override = 0;

protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapon_texture;
public:
    Weapon();

    ~Weapon() override;

    void update(const sf::Vector2f &position, std::pair<std::optional<DIRECTIONS>, DIRECTIONS> facingDirection, const float &dt) override = 0;

    virtual void update(const sf::Vector2f &position, std::string animation, const float &dt) = 0;

    void render(sf::RenderTarget &target) override = 0;

    virtual void attackEnemy(Entity *pEntity) = 0;
};