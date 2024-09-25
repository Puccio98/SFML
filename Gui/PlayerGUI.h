#ifndef SFML_PLAYERGUI_H
#define SFML_PLAYERGUI_H

#include "../Entities/Player.h"
#include "HealthBar.h"

namespace GUI {

    class PlayerGUI {

    private:
        Player *player;
        sf::Font font;
        sf::VideoMode resolution;
        GUI::HealthBar *hpBar;

        void initFont();

    public:
        explicit PlayerGUI(Player *player, sf::VideoMode &resolution);

        virtual ~PlayerGUI();

        void update(const float &dt);

        void render(sf::RenderTarget &target);
    };

}
#endif //SFML_PLAYERGUI_H
