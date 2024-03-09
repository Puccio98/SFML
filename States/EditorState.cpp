#include "EditorState.h"

EditorState::EditorState(StateData &stateData) :
        State(stateData),
        pauseMenuState(PauseMenuState(stateData)) {
    this->initVariables();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
    this->initTexts();
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
        target->draw(this->cursorText);
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

    if (!this->pauseMenuState.isPaused()) {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            this->tilemap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            this->tilemap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            this->tilemap->changeTile();
        }
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
    this->selectorRect.setFillColor(sf::Color(255, 255, 255, 100));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Red);
    this->selectorRect.setTexture(&this->tilemap->getTileTextureSheet());
    this->selectorRect.setTextureRect(this->tilemap->getTextureRect());
}

void EditorState::updateGui() {
    this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData.gridSize,
                                   this->mousePosGrid.y * this->stateData.gridSize);
    this->selectorRect.setTextureRect(this->tilemap->getTextureRect());

    std::stringstream ss;
    this->cursorText.setPosition(this->mousePosView.x + 20, this->mousePosView.y - 20);
    ss << this->mousePosView.x << " x " << this->mousePosView.y << "\n";
    this->cursorText.setString(ss.str());
}

void EditorState::renderGui(sf::RenderTarget *target) {
    this->tilemap->render(*target);
}

void EditorState::initTexts() {
    this->cursorText.setFont(*this->stateData.font);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
}
