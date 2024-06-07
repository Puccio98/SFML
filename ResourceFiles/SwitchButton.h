//
// Created by malte on 02/06/2024.
//

#ifndef SFML_SWITCHBUTTON_H
#define SFML_SWITCHBUTTON_H


#include "Button.h"

namespace GUI {

    class SwitchButton : public GUI::Button {
    public:
        SwitchButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                     unsigned int characterSize, const CssColor &text_color, const CssColor &button_color,
                     unsigned short id);

        SwitchButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                     unsigned int characterSize, const CssColor &text_color, const CssColor &button_color);

        ~SwitchButton() override;

        void update(sf::Vector2f mousePos) override;

        void handleEvent(sf::Event &event, sf::Vector2f mousePos) override;

        bool isActive() const;

    private:
        bool active = false;
    };
}

#endif //SFML_SWITCHBUTTON_H
