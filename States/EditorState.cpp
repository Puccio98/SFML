#include "EditorState.h"
#include "../Gui/PushButton.h"
#include "../Gui/SwitchButton.h"
#include "../Gui/Utils.h"

EditorState::EditorState(StateData &stateData) :
        State(stateData),
        pauseMenuState(PauseMenuState(stateData)) {
    this->initButtonsKeyLabel();
    this->sideBar = new GUI::Sidebar(stateData.graphicsSettings->resolution, *stateData.font, this->buttonsKeyLabel);

    this->initVariables();
    this->initView();
    State::initKeybinds("Config/editorstate_keybinds.ini");

    this->initGui();
}

EditorState::~EditorState() {
    delete this->sideBar;
    delete this->tileMap;
    delete this->textureSelector;
}

void EditorState::update(const float &dt) {
    if (!pauseMenuState.isPaused()) {
        State::update(dt, this->view);
        this->updateInput(dt);
        this->updateGui();
        this->updateSidebar(dt);
        if (this->clock.getElapsedTime() > this->textureSelectorTimer) {
            this->showTextureSelector = false;
        }
    } else {
        pauseMenuState.update(dt);
    }
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target) {
        target = this->stateData.window;
    }

    this->renderGui(target);

    if (!pauseMenuState.isPaused() && !this->textureSelector->isActive() &&
        !this->sideBar->getGlobalBounds().contains(this->mousePosWindow.x, this->mousePosWindow.y)) {
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
    this->buttonsKeyLabel.emplace_back("OPEN_TEXTURE_SELECTOR", "TS", false);
    this->buttonsKeyLabel.emplace_back("TOGGLE_TILES", "T", true);
    this->buttonsKeyLabel.emplace_back("SAVE_TEXTURE_MAP", "SV", false);
    this->buttonsKeyLabel.emplace_back("TOGGLE_COLLISIONS", "COL", true);
    this->buttonsKeyLabel.emplace_back("CLEAR_MAP", "R", false);
}

void EditorState::updateSidebar(float dt) {
    this->sideBar->update(dt, this->mousePosWindow);

    if (this->sideBar->isButtonClicked("OPEN_TEXTURE_SELECTOR")) {
        this->showTextureSelector = !this->showTextureSelector;
        this->clock.restart();
    }

    if (this->sideBar->isButtonClicked("TOGGLE_TILES")) {
    }

    if (this->sideBar->isButtonClicked("SAVE_TEXTURE_MAP")) {
        this->tileMap->saveToFile("Resources/map/map.slmp");
    }

    if (this->sideBar->isButtonClicked("TOGGLE_COLLISIONS")) {
        auto i = std::find(this->tileTypes.begin(), this->tileTypes.end(), TILE_TYPES::COLLISION);
        if (i != this->tileTypes.end()) {
            this->tileTypes.erase(i);
        } else {
            this->tileTypes.push_back(TILE_TYPES::COLLISION);
        }
    }

    if (this->sideBar->isButtonClicked("CLEAR_MAP")) {
        this->tileMap->clear();
    }
}

//Initializer Functions
void EditorState::initVariables() {
    this->showTextureSelector = false;
    this->tileTexturePath = "Resources/images/tiles/nuovo_tilesheet.png";
    this->tileMap = new Tilemap("Resources/map/map.slmp", *this->stateData.font, true);
    this->tileTypes.push_back(TILE_TYPES::DEFAULT);

    this->cameraSpeed = 300.f;
}

void EditorState::initView() {
    const sf::VideoMode vm = this->stateData.getCurrentVideoMode();
    this->view.setSize(sf::Vector2f(vm.width, vm.height));
    this->view.setCenter(vm.width / 2.f, vm.height / 2.f);
}

void EditorState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["CLOSE"]) { this->endState(); }
        if (event.key.code == this->keybinds["PAUSE"]) { this->pauseMenuState.setPause(true); }
    }

    if (!this->pauseMenuState.isPaused()) {
        // se sidebar
        if (this->sideBar->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow))) {
            this->sideBar->handleEvent(event, dt, this->mousePosWindow);
        }

        // se non è sidebar
        if (!this->sideBar->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow))) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                this->openTextureSelector();
                this->textureSelector->setSelectedTile(1, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                this->openTextureSelector();
                this->textureSelector->setSelectedTile(-1, 0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                this->openTextureSelector();
                this->textureSelector->setSelectedTile(0, -1);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                this->openTextureSelector();
                this->textureSelector->setSelectedTile(0, 1);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                this->setAllToFalse();
            }
        }
    }
}

void EditorState::openTextureSelector() {
    clock.restart();
    showTextureSelector = true;
}

/**
 * Chiude EditorState se è stata richiesta la chiusura del gioco da menu di pausa o direttamente da gamestate
 * @return
 */
bool EditorState::isQuit() const {
    return this->quit || this->pauseMenuState.isQuit();
}

void EditorState::initGui() {
    const sf::VideoMode vm = this->stateData.graphicsSettings->resolution;
    this->textureSelector = new TextureSelector(
            this->stateData.window->getSize().x - this->tileMap->getTileTextureSheet().getSize().x -
            this->sideBar->getSize().x, 0.f, this->stateData.gridSize,
            this->tileMap->getTileTextureSheet());
    this->previewTexture.setSize(sf::Vector2f(this->stateData.gridSize, this->stateData.gridSize));
    this->previewTexture.setFillColor(sf::Color(255, 255, 255, 100));
    this->previewTexture.setOutlineThickness(1.f);
    this->previewTexture.setOutlineColor(sf::Color::Red);
    this->previewTexture.setTexture(&this->tileMap->getTileTextureSheet());
    auto a = this->textureSelector->getSelected().getPosition();
    this->previewTexture.setTextureRect(sf::IntRect(a.x, a.y, this->stateData.gridSize, this->stateData.gridSize));
}

void EditorState::updateGui() {
    if (this->showTextureSelector) {
        this->textureSelector->update(this->mousePosWindow);
    }

    if (!this->textureSelector->isActive()) {
        auto tileTexturePosition = this->textureSelector->getSelectedRelativePosition();
        this->previewTexture.setTextureRect(
                sf::IntRect(tileTexturePosition.x, tileTexturePosition.y, this->stateData.gridSize,
                            this->stateData.gridSize));
        this->previewTexture.setPosition(this->getPosGrid(VIEW_TYPES::VIEW).x * this->stateData.gridSize,
                                         this->getPosGrid(VIEW_TYPES::VIEW).y * this->stateData.gridSize);
    }

    this->updateMouseDebug();
}

void EditorState::renderGui(sf::RenderTarget *target) {
    target->setView(this->view);
    this->tileMap->render(*target);
    target->setView(this->stateData.window->getDefaultView());

    if (this->showTextureSelector) {
        this->textureSelector->render(*target);
    }

    this->sideBar->render(*target);
}


void EditorState::updateInput(const float &dt) {
    this->updateView(dt);

    if (!this->sideBar->getGlobalBounds().contains(static_cast<sf::Vector2f>(this->mousePosWindow))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (this->textureSelector->isActive()) {
                this->textureSelector->setSelectedTile(mousePosWindow);
            } else {
                GUI::SwitchButton *switchBtn = dynamic_cast<GUI::SwitchButton *>(this->sideBar->getButton(
                        "TOGGLE_TILES"));
                if (switchBtn && switchBtn->isActive()) {
                    addTile();
                } else {
                    addTexture();
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (this->textureSelector->isActive()) {

            } else {
                int grid_x = this->getPosGrid(VIEW_TYPES::VIEW).x;
                int grid_y = this->getPosGrid(VIEW_TYPES::VIEW).y;
                if (!this->positionMap[{grid_x, grid_y}]) {
                    this->tileMap->removeTile(grid_x,
                                              grid_y);
                }
                this->positionMap[{grid_x, grid_y}] = true;
            }
        }
    }
}

void EditorState::addTile() {
    TileData tileData;
    tileData.gridSize = stateData.gridSize;
    tileData.index_x = getPosGrid(VIEW_TYPES::VIEW).x;
    tileData.index_y = getPosGrid(VIEW_TYPES::VIEW).y;
    tileData.index_z = tileMap->getMap()[tileData.index_x][tileData.index_y].size();
    tileData.types = tileTypes; // Copia contenuto del vettore :D

    if (!positionMap[{tileData.index_x, tileData.index_y}]) {
        tileMap->addTile(tileData);
    }
    positionMap[{tileData.index_x, tileData.index_y}] = true;
}

void EditorState::addTexture() {
    int index_x = getPosGrid(VIEW_TYPES::VIEW).x;
    int index_y = getPosGrid(VIEW_TYPES::VIEW).y;
    this->tileMap->addTexture(index_x, index_y, this->textureSelector->getSelectedRelativePosition());
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
