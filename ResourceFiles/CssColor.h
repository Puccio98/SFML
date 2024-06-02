#ifndef SFML_CSSCOLOR_H
#define SFML_CSSCOLOR_H

#include <System/Vector2.hpp>
#include <Graphics/Color.hpp>

struct CssColor {

    CssColor(sf::Color idle, sf::Color hover, sf::Color active) : idle(idle), hover(hover), active(active) {}

    virtual ~CssColor() = default;

    sf::Color idle;
    sf::Color hover;
    sf::Color active;
};

#endif //SFML_CSSCOLOR_H
