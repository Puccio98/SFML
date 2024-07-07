#ifndef SFML_MELEEWEAPON_H
#define SFML_MELEEWEAPON_H


#include "../../Item.h"

class MeleeWeapon : Item {
private:
protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapon_texture;

public:
    MeleeWeapon();

    ~MeleeWeapon() override;

    virtual void update(const sf::Vector2f &position) = 0;


    virtual void render(sf::RenderTarget &target) = 0;

};


#endif //SFML_MELEEWEAPON_H
