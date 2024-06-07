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
        return {sf::Color(3, 4, 94, 255),
                sf::Color(0, 119, 182, 255),
                sf::Color(0, 180, 216, 255)};
    }

    static CssColor ClassicText() {
        return {sf::Color(0, 180, 216, 255),
                sf::Color(144, 224, 239, 255),
                sf::Color(202, 240, 248, 255)};
    }
};

#endif //SFML_CSSCOLOR_H
