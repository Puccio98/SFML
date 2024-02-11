//
// Created by malte on 28/01/2024.
//

#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states, sf::Font &font) : State(window, supportedKeys, states, font) {
    this->initBackground();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
    this->initDropDownLists();
}

SettingsState::~SettingsState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
    for (auto &ddl: this->dropDownList) {
        delete ddl.second;
    }
}

void SettingsState::update(const float &dt) {
    State::update(dt);

    this->updateMousePositions();
    this->updateButtons();
    updateDropDownLists();
}

void SettingsState::updateDropDownLists() {
    for (auto &ddl: dropDownList) {
        ddl.second->update(mousePosView);
    }
}


void SettingsState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }

    target->draw(this->background);
    this->renderButtons(*target);
    renderDropDownLists(target);
}

void SettingsState::renderDropDownLists(sf::RenderTarget *target) {
    for (auto &ddl: dropDownList) {
        ddl.second->render(*target);
    }
}

void SettingsState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }

    for (auto &button: this->buttons) {
        button.second->handleEvent(event, mousePosView);
    }

    for (auto &ddl: this->dropDownList) {
        ddl.second->handleEvent(event, mousePosView);
    }
}

void SettingsState::initBackground() {
    this->background.setSize(
            sf::Vector2f(static_cast<float>(this->window->getSize().x),
                         static_cast<float>(this->window->getSize().y))
    );
    this->background.setFillColor(sf::Color::White);
}

void SettingsState::renderButtons(sf::RenderTarget &target) {
    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void SettingsState::initButtons() {
    this->buttons["EXIT_STATE"] = new GUI::Button(100, 400, 150, 50, &this->font, "Back", 50,
                                                  sf::Color(120, 50, 80, 200),
                                                  sf::Color(150, 50, 80, 250),
                                                  sf::Color(90, 40, 60, 50),
                                                  sf::Color(120, 50, 80, 0),
                                                  sf::Color(150, 50, 80, 0),
                                                  sf::Color(90, 40, 60, 0));

}

void SettingsState::updateButtons() {
    for (auto &button: this->buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }

    for (auto &ddl: this->dropDownList) {
        ddl.second->update(mousePosView);
    }
}

void SettingsState::initDropDownLists() {
    std::vector<std::string> options = {"1920x1080", "800x600", "640x480"};
    this->dropDownList["RESOLUTION"] = new GUI::DropDownList(100, 100, 200, 50, font, options);
}
