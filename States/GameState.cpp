#include "GameState.h"

GameState::GameState(StateData &stateData)
        : State(stateData), pauseMenuState(PauseMenuState(stateData)) {

    State::initKeybinds("Config/gamestate_keybinds.ini");
    this->initView();
    this->initTextures();
    this->initTilemap();
    this->initPlayer();
    this->initPlayerGUI(this->player);
}

GameState::~GameState() {
    delete this->player;
    delete this->playerGUI;
}

void GameState::update(const float &dt) {
    //per debug
    this->updateMouseDebug();
    if (!pauseMenuState.isPaused()) {
        State::update(dt, this->view);
        this->updateView(dt);
        this->updateInput(dt);
        this->updateEntity(dt, *this->player);
        this->playerGUI->update(dt);
    } else {
        pauseMenuState.update(dt);
    }
}

void GameState::render(sf::RenderTarget *target = nullptr) {
    if (!target)
        target = this->stateData.window;

    // renderizziamo mappa e giocatore tramite view, poi crea una Callback function o simile per gestire cambio di view in renderizzazione
    target->setView(this->view);
    for (int layerIndex = 0; layerIndex <= this->tilemap->getMaxLayerIndex(); layerIndex++) {
        this->tilemap->render(*target, this->player, layerIndex);
        if (layerIndex == this->player->getLayer()) {
            this->player->render(*target);
        }
    }

    target->setView(this->stateData.window->getDefaultView());
    // view standard
    this->playerGUI->render(*target);

    // per debug
    target->draw(this->mouseDebug);

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

    this->player->setDirection(direction, dt);
}

void GameState::initTextures() {
    if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/images/sprites/player/PLAYER_SHEET.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_IDLE_TEXTURE";
    }
}

void GameState::initPlayer() {
    this->player = new Player(380, 340, this->textures["PLAYER_SHEET"], *this->tilemap);
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

/**
 * Chiude gamestate se è stata richiesta la chiusura del gioco da menu di pausa o direttamente da gamestate
 * @return
 */
bool GameState::isQuit() const {
    return this->quit || this->pauseMenuState.isQuit();
}

void GameState::initTilemap() {
    this->tilemap = new Tilemap("Resources/map/map.slmp", *this->stateData.font);
}

void GameState::initView() {
    this->view.setSize(sf::Vector2f(this->stateData.graphicsSettings->resolution.width,
                                    this->stateData.graphicsSettings->resolution.height));
    this->view.setCenter(this->stateData.graphicsSettings->resolution.width / 2.f,
                         this->stateData.graphicsSettings->resolution.height / 2.f);

}

void GameState::updateView(const float &dt) {
    auto pos = this->player->getPosition();
    auto size = this->player->getSize();
    //floor serve perchè setCenter sarebbe meglio passargli degli interi per non sminchiare il render
    this->view.setCenter(std::floor(pos.x + size.width / 2), std::floor(pos.y + size.height / 2));
}

void GameState::updateEntity(const float &dt, Entity &entity) {
    // Ask entity next Movement Data
    ///ATTENZIONE: potrebbe essere che in futuro ci siano entity che non hanno Movement o HitboxComponent, in tal caso, qui va cambiato
    MovementData sprite_next_md = entity.getMovementComponent()->nextMovementData(dt);
    sf::RectangleShape next_hitbox_rs = entity.getHitboxComponent()->getHitboxRectangleShapeFromPosition(
            sprite_next_md.position);
    sf::RectangleShape current_hitbox_rs = entity.getHitboxComponent()->getHitboxRectangleShapeFromPosition(
            entity.getMovementComponent()->md.position);

    // Ask map if entity is allowed in next position relative to current position
    std::tuple<bool, bool> forbidden_directions = this->tilemap->checkCollision(current_hitbox_rs,
                                                                                next_hitbox_rs);
    // If not, calculate next allowed position
    if (std::get<0>(forbidden_directions) || std::get<1>(forbidden_directions)) {
        sprite_next_md = entity.getMovementComponent()->nextMovementData(dt, forbidden_directions);
    }
    // Update the entity movement data to the correct ones
    entity.update(sprite_next_md, dt);
}

void GameState::initPlayerGUI(Player *_player) {
    this->playerGUI = new GUI::PlayerGUI(_player);
}
