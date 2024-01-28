//
// Created by malte on 28/01/2024.
//

#include "PauseMenuState.h"

void PauseMenuState::updateInput(const float &dt) {

}

void PauseMenuState::render(sf::RenderTarget *target) {

}

void PauseMenuState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["PAUSE"] ||
            event.key.code == this->keybinds["CLOSE"]) { this->paused = false; }
    }

}


PauseMenuState::PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                               std::stack<State *> *states) : State(window, supportedKeys, states) {
    State::initKeybinds("Config/menustate_keybinds.ini");

}

PauseMenuState::~PauseMenuState() {

}

bool PauseMenuState::isPaused() const {
    return paused;
}

void PauseMenuState::setPause(bool pause) {
    this->paused = pause;

}

void PauseMenuState::update(const float &dt) {
    State::update(dt);
}
