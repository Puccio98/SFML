//
// Created by malte on 28/01/2024.
//

#include "PauseMenuState.h"

void PauseMenuState::updateInput(const float &dt) {

}

void PauseMenuState::render(sf::RenderTarget *target) {

}

void PauseMenuState::handleEvent(sf::Event &event, const float &dt) {

}


PauseMenuState::PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                               std::stack<State *> *states) : State(window, supportedKeys, states) {

}

PauseMenuState::~PauseMenuState() {

}
