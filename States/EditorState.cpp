#include "EditorState.h"
#include "../Gui/PushButton.h"
#include "../Gui/SwitchButton.h"
#include "../Gui/Utils.h"

EditorState::EditorState(StateData &stateData) :
        State(stateData),
        pauseMenuState(PauseMenuState(stateData)) {
    this->initButtonsKeyLabel();
    this->sideBar = new GUI::Sidebar(this->dvm, *stateData.font, this->buttonsKeyLabel);

    this->initVariables();
    this->initView();
    State::initKeybinds("Config/editorstate_keybinds.ini");

    this->initGui();
}

EditorState::~EditorState() {
    delete this->sideBar;
    delete this->tileMap;
    delete this->tileTextureSelector;
    delete this->enemyTextureSelector;
}

void EditorState::update(const float &dt) {
    if (!pauseMenuState.isPaused()) {
        State::update(dt);
        this->updateInput(dt);
        this->updateGui();
        this->updateSidebar(dt);
    } else {
        pauseMenuState.update(dt);
    }
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->stateData.window;
    }

    this->renderGui(target);

    if (!pauseMenuState.isPaused() && !this->tileTextureSelector->isActive() &&
        !this->enemyTextureSelector->isActive() &&
        !this->sideBar->getGlobalBounds().contains(this->mousePosView.x, this->mousePosView.y)) {
        target->draw(this->mouseDebug);


        target->setView(this->view);
        target->draw(this->previewTexture);
        target->setView(this->stateData.window->getDefaultView());
    }

    if (pauseMenuState.isPaused()) {
        pauseMenuState.render(target);
    }
}


void EditorState::initButtonsKeyLabel() {
    this->buttonsKeyLabel.emplace_back("OPEN_TEXTURE_SELECTOR", "TS", true);
    this->buttonsKeyLabel.emplace_back("OPEN_ENEMY_TEXTURE_SELECTOR", "ES", true);
    this->buttonsKeyLabel.emplace_back("TOGGLE_TILES", "T", true);
    this->buttonsKeyLabel.emplace_back("SAVE_TEXTURE_MAP", "SV", false);
    this->buttonsKeyLabel.emplace_back("TOGGLE_COLLISIONS", "COL", true);
    this->buttonsKeyLabel.emplace_back("CLEAR_MAP", "R", false);

    this->singleChoiceButtons.emplace_back("OPEN_TEXTURE_SELECTOR");
    this->singleChoiceButtons.emplace_back("OPEN_ENEMY_TEXTURE_SELECTOR");
    this->singleChoiceButtons.emplace_back("TOGGLE_TILES");
}

void EditorState::updateSidebar(float dt) {
    this->sideBar->update(dt, this->mousePosView);

    if (this->sideBar->isButtonClicked("OPEN_TEXTURE_SELECTOR")) {
        this->tileTextureSelector->restartTimer();
        this->disableSingleChoiceButtons("OPEN_TEXTURE_SELECTOR");
    }

    if (this->sideBar->isButtonClicked("OPEN_ENEMY_TEXTURE_SELECTOR")) {
        this->enemyTextureSelector->restartTimer();
        this->disableSingleChoiceButtons("OPEN_ENEMY_TEXTURE_SELECTOR");
    }

    if (this->sideBar->isButtonClicked("TOGGLE_TILES")) {
        this->disableSingleChoiceButtons("TOGGLE_TILES");
    }

    if (this->sideBar->isButtonClicked("SAVE_TEXTURE_MAP")) {
        this->tileMap->saveToFile("Resources/map/map.slmp");
    }

    if (this->sideBar->isButtonClicked("TOGGLE_COLLISIONS")) {
        auto i = std::find(this->tileTypes.begin(), this->tileTypes.end(), TILE_BEHAVIOURS::COLLISION);
        if (i != this->tileTypes.end()) {
            this->tileTypes.erase(i);
        } else {
            this->tileTypes.push_back(TILE_BEHAVIOURS::COLLISION);
        }
    }

    if (this->sideBar->isButtonClicked("CLEAR_MAP")) {
        this->tileMap->clear();
    }
}

//Initializer Functions
void EditorState::initVariables() {
    this->tileTexturePath = "Resources/images/tiles/nuovo_tilesheet.png";
    this->tileMap = new Tilemap("Resources/map/map.slmp", *this->stateData.font, true);
    this->tileTypes.push_back(TILE_BEHAVIOURS::DEFAULT);

    this->cameraSpeed = 300.f;
}

void EditorState::initView() {
    this->view.setSize(sf::Vector2f(this->dvm.width, this->dvm.height));
    this->view.setCenter(this->dvm.width / 2.f, this->dvm.height / 2.f);
}

void EditorState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["CLOSE"]) { this->endState(); }
        if (event.key.code == this->keybinds["PAUSE"]) { this->pauseMenuState.setPause(true); }
    }

    if (!this->pauseMenuState.isPaused()) {
        // se sidebar
        if (this->sideBar->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosView))) {
            this->sideBar->handleEvent(event, dt, this->mousePosView);
        }

        // se non è sidebar
        if (!this->sideBar->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosView))) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                this->openTextureSelector();
                this->setSelectedTile(1, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                this->openTextureSelector();
                this->setSelectedTile(-1, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                this->openTextureSelector();
                this->setSelectedTile(0, -1);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                this->openTextureSelector();
                this->setSelectedTile(0, 1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                this->setAllToFalse();
            }
        }
    }
}

void EditorState::openTextureSelector() {
    this->tileTextureSelector->restartTimer();
    this->disableSingleChoiceButtons("OPEN_TEXTURE_SELECTOR");
}

/**
 * Chiude EditorState se è stata richiesta la chiusura del gioco da menu di pausa o direttamente da gamestate
 * @return
 */
bool EditorState::isQuit() const {
    return this->quit || this->pauseMenuState.isQuit();
}

void EditorState::initGui() {
    this->tileTextureSelector = new TextureSelector(
            this->dvm.width - this->tileMap->getTileTextureSheet().getSize().x -
            this->sideBar->getSize().x, 0.f, this->stateData.gridSize,
            this->tileMap->getTileTextureSheet());
    this->enemySelectorTexture.loadFromFile("Resources/images/tiles/enemy_texture_selector.png");
    this->enemyTextureSelector = new TextureSelector(
            this->dvm.width - enemySelectorTexture.getSize().x -
            this->sideBar->getSize().x, 0.f, this->stateData.gridSize,
            "Resources/images/tiles/enemy_texture_selector.png");
    this->previewTexture.setSize(sf::Vector2f(this->stateData.gridSize, this->stateData.gridSize));
    this->previewTexture.setFillColor(sf::Color(255, 255, 255, 100));
    this->previewTexture.setOutlineThickness(1.f);
    this->previewTexture.setOutlineColor(sf::Color::Red);
    this->previewTexture.setTexture(&this->tileMap->getTileTextureSheet());
    auto a = this->tileTextureSelector->getSelected().getPosition();
    this->previewTexture.setTextureRect(sf::IntRect(a.x, a.y, this->stateData.gridSize, this->stateData.gridSize));
}

void EditorState::updateGui() {
    if (this->isSwitchButtonActive("OPEN_TEXTURE_SELECTOR")) {
        this->tileTextureSelector->update(this->mousePosView);
    }

    if (this->isSwitchButtonActive("OPEN_ENEMY_TEXTURE_SELECTOR")) {
        this->enemyTextureSelector->update(this->mousePosView);
    }

    if (!this->tileTextureSelector->isActive()) {
        auto tileTexturePosition = this->tileTextureSelector->getSelectedRelativePosition();
        this->previewTexture.setTextureRect(
                sf::IntRect(tileTexturePosition.x, tileTexturePosition.y, this->stateData.gridSize,
                            this->stateData.gridSize));
        this->previewTexture.setPosition(this->getPosGrid(VIEW_TYPES::VIEW, this->view).x * this->stateData.gridSize,
                                         this->getPosGrid(VIEW_TYPES::VIEW, this->view).y * this->stateData.gridSize);
    }

    this->updateMouseDebug(this->view);
}

void EditorState::renderGui(sf::RenderTarget *target) {
    target->setView(this->view);
    this->tileMap->render(*target);
    target->setView(this->stateData.window->getDefaultView());

    if (this->isSwitchButtonActive("OPEN_TEXTURE_SELECTOR") && !this->tileTextureSelector->isTimerOver()) {
        this->tileTextureSelector->render(*target);
    }


    if (this->isSwitchButtonActive("OPEN_ENEMY_TEXTURE_SELECTOR") && !this->enemyTextureSelector->isTimerOver()) {
        this->enemyTextureSelector->render(*target);
    }

    this->sideBar->render(*target);
}


void EditorState::updateInput(const float &dt) {
    this->updateView(dt);

    if (!this->sideBar->getGlobalBounds().contains(this->mousePosView)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (this->tileTextureSelector->isActive()) {
                this->setSelectedTexture(mousePosView);
            } else if (this->enemyTextureSelector->isActive()) {
                this->setSelectedEnemy(mousePosView);
            } else {
                for (const auto &key: this->singleChoiceButtons) {
                    GUI::SwitchButton *switchBtn = dynamic_cast<GUI::SwitchButton *>(this->sideBar->getButton(key));
                    if (switchBtn->isActive()) {
                        this->executeButton(key);
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (this->tileTextureSelector->isActive()) {

            } else {
                int grid_x = this->getPosGrid(VIEW_TYPES::VIEW, this->view).x;
                int grid_y = this->getPosGrid(VIEW_TYPES::VIEW, this->view).y;
                if (!this->positionMap[{grid_x, grid_y}]) {
                    this->tileMap->removeTile(grid_x,
                                              grid_y);
                }
                this->positionMap[{grid_x, grid_y}] = true;
            }
        }
    }
}

void EditorState::addTile(TILE_TYPES type) {
    TileData tileData;
    tileData.gridSize = stateData.gridSize;
    tileData.index_x = getPosGrid(VIEW_TYPES::VIEW, this->view).x;
    tileData.index_y = getPosGrid(VIEW_TYPES::VIEW, this->view).y;
    tileData.index_z = tileMap->getMap()[tileData.index_x][tileData.index_y].size();
    tileData.behaviours = tileTypes; // Copia contenuto del vettore :D
    tileData.type = type;
    sf::Vector2i enemyGridPos = this->enemyTextureSelector->getSelectedGridPosition();
    tileData.enemy_type = enemyGridPos.x == 0 ? ENEMY_TYPES::WISP : ENEMY_TYPES::FOREST_GUY;

    if (!positionMap[{tileData.index_x, tileData.index_y}]) {
        tileMap->addTile(tileData);
    }
    positionMap[{tileData.index_x, tileData.index_y}] = true;
}

void EditorState::addTexture() {
    int index_x = getPosGrid(VIEW_TYPES::VIEW, this->view).x;
    int index_y = getPosGrid(VIEW_TYPES::VIEW, this->view).y;
    this->tileMap->addTexture(index_x, index_y, this->tileTextureSelector->getSelectedRelativePosition());
}

void EditorState::updateView(const float &dt) {
    sf::Vector2f direction(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MAP_UP"])))
        direction.y = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MAP_LEFT"])))
        direction.x = -1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MAP_DOWN"])))
        direction.y = 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["MAP_RIGHT"])))
        direction.x = 1;
    view.move(direction * cameraSpeed * dt);
}

void EditorState::setSelectedTexture(sf::Vector2f &mousePos) {
    this->tileTextureSelector->restartTimer();
    this->tileTextureSelector->setSelectedTile(mousePos);
}

void EditorState::setSelectedEnemy(sf::Vector2f &mousePos) {
    this->enemyTextureSelector->setSelectedTile(mousePos);
}

void EditorState::setSelectedTile(int dir_x, int dir_y) {
    this->tileTextureSelector->restartTimer();
    this->tileTextureSelector->setSelectedTile(dir_x, dir_y);
}

void EditorState::executeButton(const std::string &key) {
    if (key == "OPEN_TEXTURE_SELECTOR") {
        this->addTexture();
    } else if (key == "TOGGLE_TILES") {
        this->addTile(TILE_TYPES::DEFAULT);
    } else if (key == "OPEN_ENEMY_TEXTURE_SELECTOR") {
        this->addTile(TILE_TYPES::SPAWNER);
    } else {
        return;
    }
}

void EditorState::disableSingleChoiceButtons(const std::string &activeButtonKey) {
    for (const auto &button: this->singleChoiceButtons) {
        if (activeButtonKey != button) {
            GUI::SwitchButton *switchBtn = dynamic_cast<GUI::SwitchButton *>(this->sideBar->getButton(button));
            switchBtn->setActive(false);
        }
    }
}

bool EditorState::isSwitchButtonActive(std::string buttonKey) {
    GUI::SwitchButton *switchBtn = dynamic_cast<GUI::SwitchButton *>(this->sideBar->getButton(buttonKey));
    return switchBtn->isActive();
}
