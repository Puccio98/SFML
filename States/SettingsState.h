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

    //TODO Sposterei la mappa di bottoni in state
    std::map<std::string, GUI::Button *> buttons;
    GUI::DropDownList *dropDownList = nullptr;

    void initBackground();


    void initButtons();

    void updateButtons();

    void renderButtons(sf::RenderTarget &target);

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states,
                  sf::Font &font);

    ~SettingsState() override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    void update(const float &dt) override;
};

#endif //SFML_SETTINGSSTATE_H
