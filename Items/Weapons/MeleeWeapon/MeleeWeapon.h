#ifndef SFML_MELEEWEAPON_H
#define SFML_MELEEWEAPON_H


#include "../../Item.h"

class MeleeWeapon : public Item {
private:
protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapon_texture;

public:
    MeleeWeapon();

    ~MeleeWeapon() override;

    void update(const sf::Vector2f &position, const float &dt) override = 0;


    void render(sf::RenderTarget &target) override = 0;

private:
    void updateAnimation(const float &dt) override = 0;

};


#endif //SFML_MELEEWEAPON_H
