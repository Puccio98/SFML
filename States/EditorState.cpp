#include "EditorState.h"

EditorState::EditorState(StateData &stateData) :
        State(stateData),
        pauseMenuState(PauseMenuState(stateData)) {
    this->initVariables();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
    this->initTileMap();
    this->initGui();
}

EditorState::~EditorState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }

    delete this->tilemap;
}

void EditorState::update(const float &dt) {
    if (!pauseMenuState.isPaused()) {
        State::update(dt);
        this->updateMousePositions();
        this->updateGui();
        this->updateButtons();
    } else {
        pauseMenuState.update(dt);
    }
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->stateData.window;
    this->renderButtons(target);
    this->renderGui(target);

    if (!pauseMenuState.isPaused()) {
        target->draw(this->selectorRect);
    }

    if (pauseMenuState.isPaused()) {
        pauseMenuState.render(target);
    }
}


void EditorState::initButtons() {

}

void EditorState::renderButtons(sf::RenderTarget *target) {
    for (auto &button: this->buttons) {
        button.second->render(*target);
    }
}

void EditorState::updateButtons() {
    /*Updates all buttons in state and handles their functionality*/
    for (auto &button: this->buttons) {
        button.second->update(this->mousePosView);
    }

    this->tilemap->update();
}

//Initializer Functions
void EditorState::initVariables() {
}

void EditorState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["CLOSE"]) { this->endState(); }
        if (event.key.code == this->keybinds["PAUSE"]) { this->pauseMenuState.setPause(true); }
    }
}

/**
 * Chiude EditorState se è stata richiesta la chiusura del gioco da menu di pausa o direttamente da gamestate
 * @return
 */
bool EditorState::isQuit() const {
    return this->quit || this->pauseMenuState.isQuit();
}

void EditorState::initTileMap() {
    this->tilemap = new Tilemap(this->stateData.gridSize, 15, 10);
}

void EditorState::initGui() {
    this->selectorRect.setSize(sf::Vector2f(this->stateData.gridSize, this->stateData.gridSize));
    this->selectorRect.setFillColor(sf::Color::Transparent);
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Red);
}

void EditorState::updateGui() {
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData.gridSize,
                                   this->mousePosGrid.y * this->stateData.gridSize);
}

void EditorState::renderGui(sf::RenderTarget *target) {
    this->tilemap->render(*target);
}
