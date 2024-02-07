//
// Created by malte on 28/01/2024.
//

#ifndef SFML_SETTINGSSTATE_H
#define SFML_SETTINGSSTATE_H


#include "State.h"
#include "../Resource Files/DropDownList.h"

class SettingsState : public State {
private:
    sf::RectangleShape background;
    sf::Font font;

    //TODO Sposterei la mappa di bottoni in state
    std::map<std::string, GUI::Button *> buttons;
    GUI::DropDownList *dropDownList;

    void initBackground();

    //TODO spostare font in Game.cpp e passare i font ai vari stati
    void initFonts();

    void initButtons();

    void updateButtons();

    void renderButtons(sf::RenderTarget &target);

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    ~SettingsState() override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    void update(const float &dt) override;
};

#endif //SFML_SETTINGSSTATE_H
