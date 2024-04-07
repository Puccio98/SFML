#include "PauseMenuState.h"

void PauseMenuState::render(sf::RenderTarget *target) {
    target->draw(this->container);

    for (auto &button: this->buttons) {
        button.second->render(*target);
    }
    target->draw(this->menuText);
}

void PauseMenuState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["PAUSE"] || event.key.code == this->keybinds["CLOSE"]) {
            this->setPause(false);
        }
    }

    for (auto &button: this->buttons) {
        button.second->handleEvent(event, mousePosView);
    }
}


PauseMenuState::PauseMenuState(StateData &stateData)
        : State(stateData) {
    // *(new State::StateData(nullptr, stateData.window, stateData.supportedKeys, stateData.font))
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initContainer(stateData.window);
    this->initTexts();
    this->initButton();
}

void PauseMenuState::initContainer(const sf::RenderWindow *window) {
    container.setSize(sf::Vector2f(sf::Vector2f(window->getSize()) / 2.f));
    container.setFillColor(sf::Color(40, 40, 80, 200));
    container.setPosition(
            sf::Vector2f(window->getSize()) / 2.f -
            sf::Vector2f(container.getGlobalBounds().width / 2.f, container.getGlobalBounds().height / 2.f));
}

void PauseMenuState::initTexts() {
    menuText.setFont(*stateData.font);
    menuText.setFillColor(sf::Color(200, 200, 200, 200));
    menuText.setString("Paused");
    menuText.setCharacterSize(40);
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

    //Se esce da menu di pausa resetta bottoni
    if (!pause) {
        for (auto &button: this->buttons) {
            button.second->reset();
        }
    }
}

void PauseMenuState::update(const float &dt) {
    State::update(dt);
    this->updateButtons();
}

void PauseMenuState::updateButtons() {
    for (auto &button: buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["GAME"]->isPressed()) {
        this->setPause(false);
    }

    if (this->buttons["CLOSE"]->isPressed()) {
        this->setPause(false);
        this->quit = true;
    }
}

void PauseMenuState::initButton() {
    float width = 250.f;
    float height = 50.f;
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
    float basePosY = this->container.getPosition().y;

    this->buttons["GAME"] = new GUI::Button(x, basePosY + 100, width, height, this->stateData.font, "Return to Game",
                                            40,
                                            sf::Color(120, 50, 80, 200),
                                            sf::Color(150, 50, 80, 250),
                                            sf::Color(90, 40, 60, 50),
                                            sf::Color(120, 50, 80, 0),
                                            sf::Color(150, 50, 80, 0),
                                            sf::Color(90, 40, 60, 0));

    this->buttons["CLOSE"] = new GUI::Button(x, basePosY + 200, width, height, this->stateData.font, "Close", 40,
                                             sf::Color(120, 50, 80, 200),
                                             sf::Color(150, 50, 80, 250),
                                             sf::Color(90, 40, 60, 50),
                                             sf::Color(120, 50, 80, 0),
                                             sf::Color(150, 50, 80, 0),
                                             sf::Color(90, 40, 60, 0));
}
