#pragma once

#include "Button.h"

namespace GUI {
    class PushButton : public GUI::Button {
    public:
        PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                   unsigned int characterSize, const CssColor &text_color, const CssColor &button_color,
                   unsigned short id);

        PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                   unsigned int characterSize, const CssColor &text_color, const CssColor &button_color);

        ~PushButton() override;

        void update(sf::Vector2f mousePos) override;

    private:
    };
}