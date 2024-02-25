#ifndef SFML_MAINMENUSTATE_H
#define SFML_MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "../Resource Files/Button.h"

class MainMenuState : public State {
public:
    MainMenuState(StateData &stateData);

    ~MainMenuState() override;

    //Functions
    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void renderButtons(sf::RenderTarget &target);

private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    std::map<std::string, GUI::Button *> buttons;

    //Functions
    void initVariables();

    void initBackground();

    void initButtons();

    void updateButtons();


public:
    void handleEvent(sf::Event &event, const float &dt) override;
};


#endif //SFML_MAINMENUSTATE_H
