//
// Created by malte on 28/01/2024.
//

#ifndef SFML_PAUSEMENUSTATE_H
#define SFML_PAUSEMENUSTATE_H


#include "State.h"

class PauseMenuState : public State {
public:
    PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    ~PauseMenuState() override;

    void updateInput(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isPaused() const;

    void setPause(bool pause);

    void update(const float &dt) override;


private:
    bool paused = false;
};


#endif //SFML_PAUSEMENUSTATE_H
