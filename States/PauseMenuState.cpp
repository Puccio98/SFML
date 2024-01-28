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
    this->initButton();
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
    this->updateButtons();
}

void PauseMenuState::updateButtons() {
    for (auto &button: buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["GAME"]->isPressed()) {
        this->paused = false;
    }

    if (this->buttons["CLOSE"]->isPressed()) {
        this->quit = true;
    }

}

void PauseMenuState::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::PAUSEMENUSTATE::COULD NOT LOAD FONT");
    };
}

void PauseMenuState::initButton() {
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons["GAME"] = new Button(x, 300, width, height, &this->font, "Return to Game", 40,
                                       sf::Color(120, 50, 80, 200),
                                       sf::Color(150, 50, 80, 250),
                                       sf::Color(90, 40, 60, 50),
                                       sf::Color(120, 50, 80, 0),
                                       sf::Color(150, 50, 80, 0),
                                       sf::Color(90, 40, 60, 0));
    this->buttons["CLOSE"] = new Button(x, 500, width, height, &this->font, "Close", 40,
                                        sf::Color(120, 50, 80, 200),
                                        sf::Color(150, 50, 80, 250),
                                        sf::Color(90, 40, 60, 50),
                                        sf::Color(120, 50, 80, 0),
                                        sf::Color(150, 50, 80, 0),
                                        sf::Color(90, 40, 60, 0));
}
