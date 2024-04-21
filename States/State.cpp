#include "State.h"

State::State(StateData &stateData) : stateData(stateData) {
    this->quit = false;
}

State::~State() = default;

void State::updateMousePositions(const sf::View &view) {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->stateData.window);

    this->stateData.window->setView(view);
    this->mousePosView = this->stateData.window->mapPixelToCoords(sf::Mouse::getPosition(*this->stateData.window));
    this->stateData.window->setView(this->stateData.window->getDefaultView());
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

    while (this->stateData.window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            this->stateData.window->close();

        this->handleEvent(event, dt);
    }
}

void State::update(const float &dt) {
    this->updateMousePositions(this->stateData.window->getDefaultView());
    this->pollEvents(dt);
}

void State::update(const float &dt, const sf::View &_view) {
    this->updateMousePositions(_view);
    this->pollEvents(dt);
}

void State::initKeybinds(std::string keybindsFilePath) {
    std::ifstream ifs(keybindsFilePath);

    if (ifs.is_open()) {
        std::string key;
        std::string key_value;
        while (ifs >> key >> key_value) {
            this->keybinds[key] = this->stateData.supportedKeys->at(key_value);
        }
    }

    ifs.close();
}

bool State::isQuit() const {
    return quit;
}

sf::Vector2i State::getPosGrid(VIEW_TYPES viewType) const {
    switch (viewType) {
        case VIEW_TYPES::SCREEN:
            return {
                    (this->mousePosScreen.x) / static_cast<int > (this->stateData.gridSize),
                    (this->mousePosScreen.y) / static_cast<int > (this->stateData.gridSize)
            };
        case VIEW_TYPES::WINDOW:
            return {
                    (this->mousePosWindow.x) / static_cast<int > (this->stateData.gridSize),
                    (this->mousePosWindow.y) / static_cast<int > (this->stateData.gridSize)
            };
        case VIEW_TYPES::VIEW: {
            return {
                    (static_cast<int>(this->mousePosView.x)) / static_cast<int > (this->stateData.gridSize),
                    (static_cast<int>(this->mousePosView.y)) / static_cast<int > (this->stateData.gridSize)
            };
        }
        default:
            return {0, 0};
    }

}



