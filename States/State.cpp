#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states,
             sf::Font &font) : font(font) {
    this->states = states;
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}

State::~State() = default;

void State::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

__attribute__((unused)) void State::debugMousePosition() const {
    system("cls");
    std::cout << "posScreen x" << this->mousePosScreen.x << "\n";
    std::cout << "posWindow x" << this->mousePosWindow.x << "\n";
    std::cout << "posView x" << this->mousePosView.x << "\n";
}

void State::endState() {
    this->quit = true;
}

void State::pollEvents(const float &dt) {
    sf::Event event{};

    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->window->close();

        this->handleEvent(event, dt);
    }
}

void State::update(const float &dt) {
    this->pollEvents(dt);
}

void State::initKeybinds(std::string keybindsFilePath) {
    std::ifstream ifs(keybindsFilePath);

    if (ifs.is_open()) {
        std::string key;
        std::string key_value;
        while (ifs >> key >> key_value) {
            this->keybinds[key] = this->supportedKeys->at(key_value);
        }
    }

    ifs.close();
}

bool State::isQuit() const {
    return quit;
}



