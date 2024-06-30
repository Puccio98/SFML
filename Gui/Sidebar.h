#ifndef SFML_SIDEBAR_H
#define SFML_SIDEBAR_H

#include <Graphics/RectangleShape.hpp>
#include <Window/VideoMode.hpp>
#include <Graphics/Font.hpp>
#include "Button.h"
#include "Structs/SidebarButton.h"

namespace GUI {
    class Sidebar {
    private:
        sf::VideoMode vm;
        sf::RectangleShape container;
        sf::Font font;
        std::map<std::string, GUI::Button *> buttons;
        std::vector<SidebarButton> buttonsKeyLabel;

        void initContainer();

        void initButtons();

        void createButton(const std::string &key, const std::string &label, int positionMultiplier,
                          bool isSwitch);

    public:
        virtual ~Sidebar();

        void update(float dt, sf::Vector2<int> mousePosition);

        void handleEvent(sf::Event &event, const float &dt, sf::Vector2<int> mousePosition);

        void render(sf::RenderTarget &target);

        bool isButtonClicked(std::string key);

        GUI::Button *getButton(std::string key);

        sf::FloatRect getGlobalBounds();

        sf::Vector2f getSize();

        Sidebar(sf::VideoMode &vm, sf::Font &font, std::vector<SidebarButton> &buttonsKeyLabel);
    };
}


#endif //SFML_SIDEBAR_H
