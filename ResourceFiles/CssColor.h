#ifndef SFML_CSSCOLOR_H
#define SFML_CSSCOLOR_H

#include <System/Vector2.hpp>
#include <Graphics/Color.hpp>

struct CssColor {
    CssColor(sf::Color idle, sf::Color hover, sf::Color active) : idle(idle), hover(hover), active(active) {}

    ~CssColor() = default;  // No need for virtual here

    sf::Color idle;
    sf::Color hover;
    sf::Color active;

    static CssColor ClassicButton() {
        return {sf::Color(120, 50, 80, 0),
                sf::Color(150, 50, 80, 0),
                sf::Color(90, 40, 60, 0)};
    }

    static CssColor ClassicText() {
        return {sf::Color(120, 50, 80, 200),
                sf::Color(150, 50, 80, 250),
                sf::Color(90, 40, 60, 50)};
    }
};

#endif //SFML_CSSCOLOR_H
