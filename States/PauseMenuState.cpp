#include "PauseMenuState.h"

void PauseMenuState::updateInput(const float &dt) {

}

void PauseMenuState::render(sf::RenderTarget *target) {
    target->draw(this->container);

    for (auto &button: this->buttons) {
        button.second->render(*target);
    }
    target->draw(this->menuText);
}

void PauseMenuState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["PAUSE"] ||
            event.key.code == this->keybinds["CLOSE"]) { this->paused = false; }
    }

}


PauseMenuState::PauseMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys)
        : State(window,
                supportedKeys,
                nullptr) {
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initFonts();
    this->initContainer(window);
    this->initTexts();
}

void PauseMenuState::initContainer(const sf::RenderWindow *window) {
    container.setSize(sf::Vector2f(sf::Vector2f(window->getSize()) / 2.f));
    container.setFillColor(sf::Color::Red);
    container.setPosition(
            sf::Vector2f(window->getSize()) / 2.f -
            sf::Vector2f(container.getGlobalBounds().width / 2.f, container.getGlobalBounds().height / 2.f));
}

void PauseMenuState::initTexts() {
    menuText.setFont(font);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("PAUSED");
    menuText.setCharacterSize(60);
    menuText.setPosition(
            container.getPosition().x + container.getSize().x / 2.f -
            menuText.getGlobalBounds().width / 2.f,
            container.getPosition().y + 20.f
    );
}

PauseMenuState::~PauseMenuState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
}

bool PauseMenuState::isPaused() const {
    return paused;
}

void PauseMenuState::setPause(bool pause) {
    this->paused = pause;

}

void PauseMenuState::update(const float &dt) {
    State::update(dt);
    this->updateMousePositions();
    this->updateInput(dt);
}

void PauseMenuState::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::PAUSEMENUSTATE::COULD NOT LOAD FONT");
    };
}
