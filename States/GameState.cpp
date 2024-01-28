

#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
        : State(window,
                supportedKeys, states), pauseMenuState(PauseMenuState(window, supportedKeys)) {

    State::initKeybinds("Config/gamestate_keybinds.ini");
    this->initTextures();
    this->initPlayer();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::update(const float &dt) {
    if (!pauseMenuState.isPaused()) {
        State::update(dt);
        this->updateMousePositions();
        this->updateInput(dt);
        this->player->update(dt);
    } else {
        pauseMenuState.update(dt);
    }
}

void GameState::render(sf::RenderTarget *target = nullptr) {
    if (!target)
        target = this->window;
    this->player->render(*target);
    if (pauseMenuState.isPaused()) {
        pauseMenuState.render(target);
    }
}

void GameState::updateInput(const float &dt) {
    //Update player input
    sf::Vector2f direction(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_UP"])))
        direction.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_LEFT"])))
        direction.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_DOWN"])))
        direction.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_RIGHT"])))
        direction.x = 1;
    this->player->move(direction, dt);
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/images/sprites/player/PLAYER_SHEET.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
    }
}

void GameState::initPlayer() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["CLOSE"]) { this->endState(); }
        if (event.key.code == this->keybinds["PAUSE"]) { this->pauseMenuState.setPause(true); }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        this->player->attack(dt);
    }
}

bool GameState::isQuit() const {
    return this->quit || this->pauseMenuState.isQuit();
}


