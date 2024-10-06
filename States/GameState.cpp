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
    //delete this->player;
    delete this->playerGUI;
    for (auto *entity: this->entities) {
        delete entity;
    }
    this->entities.clear();
}

void GameState::update(const float &dt) {
    EntityDimensionData edd(this->player->getHitboxComponent()->getPosition(), this->player->getSize());

    //per debug
    this->updateMouseDebug(this->view);
    if (!pauseMenuState.isPaused()) {
        State::update(dt); //, this->view
        this->updateView(dt);
        this->updateInput(dt);
        this->updateEntities(dt);
        this->tilemap->update(*this->stateData.window, edd, dt, entities);
        this->playerGUI->update(dt);
        if (this->player->getCurrentHp() == 0) {
            this->quit = true;
        }
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
        EntityDimensionData edd(this->player->getHitboxComponent()->getPosition(), this->player->getSize());
        this->tilemap->renderLayer(*target, edd, layerIndex);
        this->renderEntities(layerIndex, target);
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
    if (!this->textures["PLAYER_SHEET"].loadFromFile(
            "Resources/images/sprites/entities/player/player_sheet_x3.png")) {
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
    }
}

void GameState::initPlayer() {
    this->player = new Player(this->dvm.width / 2 - 130, this->dvm.height / 2 - 125, this->textures["PLAYER_SHEET"]);
    this->entities.push_back(this->player);
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
    this->view.setSize(sf::Vector2f(this->dvm.width,
                                    this->dvm.height));
    this->view.setCenter(this->dvm.width / 2.f,
                         this->dvm.height / 2.f);

}

void GameState::updateView(const float &dt) {
    auto pos = this->player->getPosition();
    auto size = this->player->getSize();
    //floor serve perchè setCenter sarebbe meglio passargli degli interi per non sminchiare il renderLayer
    this->view.setCenter(std::floor(pos.x + size.x / 2), std::floor(pos.y + size.y / 2));
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
    this->playerGUI = new GUI::PlayerGUI(_player, this->stateData.graphicsSettings->resolution);
}

void GameState::updateEntities(const float &dt) {
    for (auto entity: this->entities) {
        this->updateEntity(dt, *entity);
    }

    for (auto entity: this->entities) {
        if (player != entity && player->getLayer() == entity->getLayer() && !player->isInvincible()) {
            if (player->getHitboxComponent()->checkIntersect(
                    entity->getHitboxComponent()->getHitbox().getGlobalBounds())) {
                player->takeDamage();
            }
        }
    }
}

void GameState::renderEntities(int layerIndex, sf::RenderTarget *target) {
    std::sort(this->entities.begin(), this->entities.end(), compareByBaseline);
    for (auto entity: this->entities) {
        if (layerIndex == entity->getLayer()) {
            entity->render(*target);
        }
    }
}

bool GameState::compareByBaseline(const Entity *a, const Entity *b) {
    return (a->getPosition().y + a->getSize().y) < (b->getPosition().y + b->getSize().y);
}
