//
// Created by malte on 28/01/2024.
//

#ifndef SFML_SETTINGSSTATE_H
#define SFML_SETTINGSSTATE_H


#include "State.h"
#include "../Gui/DropDownList.h"
#include "../Settings/GraphicsSettings.h"

class SettingsState : public State {
private:
    sf::RectangleShape background;
    //TODO Sposterei la mappa di bottoni in state
    std::map<std::string, GUI::Button *> buttons;
    std::map<std::string, GUI::DropDownList *> dropDownList;

    sf::Text optionsText;
    std::vector<sf::VideoMode> videoModes;

    void initVariables();

    void initBackground();

    void initDropDownLists();

    void initButtons();

    void updateButtons();

    void renderButtons(sf::RenderTarget &target);

    void initOptionsText();

public:
    SettingsState(StateData &stateData);

    ~SettingsState() override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    void update(const float &dt) override;

    void renderDropDownLists(sf::RenderTarget *target);

    void updateDropDownLists();
};

#endif //SFML_SETTINGSSTATE_H
