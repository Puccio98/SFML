#include "PauseMenuState.h"
#include "../Gui/PushButton.h"
#include "../Gui/Utils.h"

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
    this->initMenuText();
    this->initButton();
}

void PauseMenuState::initContainer(const sf::RenderWindow *window) {
    container.setSize(sf::Vector2f(sf::Vector2f(window->getSize()) / 2.f));
    container.setFillColor(sf::Color(40, 40, 80, 200));
    container.setPosition(
            sf::Vector2f(window->getSize()) / 2.f -
            sf::Vector2f(container.getGlobalBounds().width / 2.f, container.getGlobalBounds().height / 2.f));
}

void PauseMenuState::initMenuText() {
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
}

void PauseMenuState::update(const float &dt) {
    State::update(dt);
    this->updateButtons();
}

void PauseMenuState::updateButtons() {
    for (auto &button: buttons) {
        button.second->update(mousePosView);
    }

    if (this->buttons["GAME"]->isClicked()) {
        this->setPause(false);
    }

    if (this->buttons["CLOSE"]->isClicked()) {
        this->setPause(false);
        this->quit = true;
    }
}

void PauseMenuState::initButton() {
    const sf::VideoMode vm = this->stateData.graphicsSettings->resolution;
    float width = GUI::Utils::p2px(15, vm);
    float height = GUI::Utils::p2py(7, vm);
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;
    float basePosY = this->container.getPosition().y;

    auto createButton = [&](const std::string &key, const std::string &label, int yMultiplier) {
        float y = basePosY + GUI::Utils::p2py(20 + (12 * yMultiplier), vm);
        this->buttons[key] = new GUI::PushButton(x, y, width, height, this->stateData.font, label,
                                                 GUI::Utils::charSize(vm),
                                                 CssColor::ClassicText(), CssColor::ClassicButton());
    };

    createButton("GAME", "Return to Game", 0);
    createButton("CLOSE", "Close", 1);
}
