//
// Created by malte on 28/01/2024.
//

#ifndef SFML_PAUSEMENUSTATE_H
#define SFML_PAUSEMENUSTATE_H


#include "State.h"
#include "../Resource Files/Button.h"

class PauseMenuState : public State {
public:
    PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys);

    ~PauseMenuState() override;

    void updateInput(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isPaused() const;

    void setPause(bool pause);

    void update(const float &dt) override;

    void initFonts();

private:
    bool paused = false;
    sf::RectangleShape container;
    sf::Font font;
    sf::Text menuText;
    std::map<std::string, Button *> buttons;

    void initTexts();

    void initContainer(const sf::RenderWindow *window);
};


#endif //SFML_PAUSEMENUSTATE_H
