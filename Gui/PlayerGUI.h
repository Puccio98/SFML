#ifndef SFML_PLAYERGUI_H
#define SFML_PLAYERGUI_H

#include "../Entities/Player.h"
#include "ProgressBar.h"

namespace GUI {

    class PlayerGUI {

    private:
        Player *player;
        sf::Font font;

        GUI::ProgressBar *hpBar;

        void initFont();

    public:
        explicit PlayerGUI(Player *player);

        virtual ~PlayerGUI();

        void update(const float &dt);

        void render(sf::RenderTarget &target);
    };

}
#endif //SFML_PLAYERGUI_H
