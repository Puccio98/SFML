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

        unsigned short getSelectedElementId() const;

    private:
        GUI::Button *activeElement;
        std::vector<GUI::Button *> buttons;
        sf::Font &font;
        bool showList;
        unsigned int selectedElementId;
    };
}

#endif //SFML_DROPDOWNLIST_H
