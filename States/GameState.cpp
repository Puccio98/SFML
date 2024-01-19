

#include "GameState.h"

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
        : State(window,
                supportedKeys, states) {
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState() {
    delete this->player;
}

void GameState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->player->update(dt);
}

void GameState::render(sf::RenderTarget *target = nullptr) {
    if (!target)
        target = this->window;
    this->player->render(*target);
}

void GameState::updateInput(const float &dt) {
    //Update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_UP"])))
        this->player->move(0.f, -1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_LEFT"])))
        this->player->move(-1.f, 0.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_DOWN"])))
        this->player->move(0.f, 1.f, dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["MOVE_RIGHT"])))
        this->player->move(1.f, 0.f, dt);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->player->attack(dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])))
        this->endState();
}

void GameState::initKeybinds() {
    std::ifstream ifs("Config/gamestate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key;
        std::string key_value;
        while (ifs >> key >> key_value) {
            this->keybinds[key] = this->supportedKeys->at(key_value);
        }
    }
    ifs.close();
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/images/sprites/player/PLAYER_SHEET.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
    }
}

void GameState::initPlayers() {
    this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}


