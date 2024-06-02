#ifndef SFML_PUSHBUTTON_H
#define SFML_PUSHBUTTON_H

#include "Button.h"

namespace GUI {
    class PushButton : public GUI::Button {
    public:
        PushButton(float x, float y, float width, float height, sf::Font *font, const std::string &text,
                   unsigned int characterSize, const sf::Color &textIdleColor, const sf::Color &textHoverColor,
                   const sf::Color &textActiveColor, const sf::Color &idleColor, const sf::Color &hoverColor,
                   const sf::Color &activeColor, unsigned short id = 0);

        ~PushButton() override;

        void update(sf::Vector2f mousePos) override;

        void handleEvent(sf::Event &event, sf::Vector2f mousePos) override;

        void reset() override;

    private:
        bool locked = false;

    };
}

#endif //SFML_PUSHBUTTON_H
