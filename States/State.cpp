#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states) {
    this->states = states;
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->quit = false;
}

State::~State() = default;

const bool &State::getQuit() const {
    return this->quit;
}

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



