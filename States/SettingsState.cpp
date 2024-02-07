//
// Created by malte on 28/01/2024.
//

#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window, supportedKeys, states) {

    this->initFonts();
    this->initBackground();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
}

SettingsState::~SettingsState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
    delete this->dropDownList;
}

void SettingsState::update(const float &dt) {
    State::update(dt);

    this->updateMousePositions();
    this->updateButtons();
    this->dropDownList->update(mousePosView);
}


void SettingsState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->window;
    }

    target->draw(this->background);
    this->renderButtons(*target);
    this->dropDownList->render(*target);
}

void SettingsState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }
}

void SettingsState::initBackground() {
    this->background.setSize(
            sf::Vector2f(static_cast<float>(this->window->getSize().x),
                         static_cast<float>(this->window->getSize().y))
    );
    this->background.setFillColor(sf::Color::White);
}

void SettingsState::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::SETTINGSTATE::COULD NOT LOAD FONT");
    };
}

void SettingsState::renderButtons(sf::RenderTarget &target) {
    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void SettingsState::initButtons() {
    this->buttons["EXIT_STATE"] = new GUI::Button(500, 200, 150, 50, &this->font, "Quit", 50,
                                                  sf::Color(120, 50, 80, 200),
                                                  sf::Color(150, 50, 80, 250),
                                                  sf::Color(90, 40, 60, 50),
                                                  sf::Color(120, 50, 80, 0),
                                                  sf::Color(150, 50, 80, 0),
                                                  sf::Color(90, 40, 60, 0));

    std::string options[] = {"pippo", "paolo", "paperino", "topolino", "pluto"};
    this->dropDownList = new GUI::DropDownList(100, 100, 200, 50, font, options);
}

void SettingsState::updateButtons() {
    for (auto &button: this->buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["EXIT_STATE"]->isPressed()) {
        this->endState();
    }

    this->dropDownList->update(mousePosView);
}
