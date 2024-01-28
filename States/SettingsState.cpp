//
// Created by malte on 28/01/2024.
//

#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window, supportedKeys, states) {

    this->initFonts();
    this->initVariables();
    this->initBackground();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
}

SettingsState::~SettingsState() {

}

void SettingsState::updateInput(const float &dt) {

}

void SettingsState::render(sf::RenderTarget *target) {

}

void SettingsState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }
}

void SettingsState::initVariables() {

}

void SettingsState::initBackground() {

}

void SettingsState::initFonts() {

}

void SettingsState::initButtons() {

}

void SettingsState::updateButtons() {

}
