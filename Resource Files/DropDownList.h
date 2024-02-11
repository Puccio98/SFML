#ifndef SFML_DROPDOWNLIST_H
#define SFML_DROPDOWNLIST_H

#include "Button.h"

namespace GUI {
    class DropDownList {
    public:
        DropDownList(float x, float y, float width, float height, sf::Font &font, std::vector<std::string> &options,
                     unsigned default_index = 0);

        virtual ~DropDownList();

        void update(const sf::Vector2f &mousePos);

        void render(sf::RenderTarget &target);

        void handleEvent(sf::Event &event, const sf::Vector2f mousePos);

    private:
        GUI::Button *activeElement;
        short unsigned selectedElement;
        std::vector<GUI::Button *> buttons;
        sf::Font &font;
        bool showList;
    };
}

#endif //SFML_DROPDOWNLIST_H