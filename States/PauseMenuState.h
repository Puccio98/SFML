#pragma once

#include "State.h"
#include "../Gui/Button.h"

class PauseMenuState : public State {
public:
    PauseMenuState(StateData &stateData);

    ~PauseMenuState() override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isPaused() const;

    void setPause(bool pause);

    void update(const float &dt) override;


private:
    bool paused = false;
    sf::RectangleShape container;
    sf::Text menuText;
    std::map<std::string, GUI::Button *> buttons;

    void initMenuText();

    void initContainer();

    void initButton();

    void updateButtons();
};