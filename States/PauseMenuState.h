//
// Created by malte on 28/01/2024.
//

#ifndef SFML_PAUSEMENUSTATE_H
#define SFML_PAUSEMENUSTATE_H


#include "State.h"
#include "../Resource Files/Button.h"

class PauseMenuState : public State {
public:
    PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, sf::Font &font);

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

    void initTexts();

    void initContainer(const sf::RenderWindow *window);

    void initButton();

    void updateButtons();
};


#endif //SFML_PAUSEMENUSTATE_H
