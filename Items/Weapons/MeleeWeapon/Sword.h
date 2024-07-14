#ifndef SFML_SWORD_H
#define SFML_SWORD_H


#include "MeleeWeapon.h"

class Sword : MeleeWeapon {
public:
    Sword();

    ~Sword() override;


    void update(const sf::Vector2f &position) override;

    void render(sf::RenderTarget &target) override;


private:
};

#endif //SFML_SWORD_H
