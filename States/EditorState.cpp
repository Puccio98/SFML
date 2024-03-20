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
    delete this->textureSelector;
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
    if (!target) {
        target = this->stateData.window;
    }

    this->renderButtons(target);
    this->renderGui(target);

    if (!pauseMenuState.isPaused() && !this->textureSelector->isActive()) {
        target->draw(this->cursorText);
        target->draw(this->previewTexture);
    }

    if (pauseMenuState.isPaused()) {
        pauseMenuState.render(target);
    }
}


void EditorState::initButtons() {
    this->buttons["TOGGLE_TEXTURE_SELECTOR"] = new GUI::Button(this->stateData.window->getSize().x - 50, 0, 50, 50, this->stateData.font, "TS", 30,
                                                  sf::Color(120, 50, 80, 200),
                                                  sf::Color(150, 50, 80, 250),
                                                  sf::Color(90, 40, 60, 50),
                                                  sf::Color(120, 50, 80, 100),
                                                  sf::Color(150, 50, 80, 100),
                                                  sf::Color(90, 40, 60, 100));
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

    if (this->buttons["TOGGLE_TEXTURE_SELECTOR"]->isPressed()) {
        this->buttons["TOGGLE_TEXTURE_SELECTOR"]->reset();
        this->showTextureSelector = !this->showTextureSelector;
    }

    this->tilemap->update();
}

//Initializer Functions
void EditorState::initVariables() {
    this->showTextureSelector = false;
}

void EditorState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == this->keybinds["CLOSE"]) { this->endState(); }
        if (event.key.code == this->keybinds["PAUSE"]) { this->pauseMenuState.setPause(true); }
    }

    if (!this->pauseMenuState.isPaused()) {
        for (auto &button: this->buttons) {
            button.second->handleEvent(event, mousePosView);
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (this->textureSelector->isActive()) {
                this->tilemap->changeTile(this->textureSelector->getMousePosGrid());
                this->textureSelector->setSelectedTile(this->textureSelector->getMousePosGrid());
            } else {
                this->tilemap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
            if (this->textureSelector->isActive()) {

            } else {
                this->tilemap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
            this->tilemap->changeTile();
            this->textureSelector->setSelectedTile();
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
    this->previewTexture.setSize(sf::Vector2f(this->stateData.gridSize, this->stateData.gridSize));
    this->previewTexture.setFillColor(sf::Color(255, 255, 255, 100));
    this->previewTexture.setOutlineThickness(1.f);
    this->previewTexture.setOutlineColor(sf::Color::Red);
    this->previewTexture.setTexture(&this->tilemap->getTileTextureSheet());
    this->previewTexture.setTextureRect(this->tilemap->getTextureRect());

    this->textureSelector = new TextureSelector(0.f, 0.f, this->stateData.gridSize,
                                                this->tilemap->getTileTextureSheet());
}

void EditorState::updateGui() {
    if(this->showTextureSelector) {
        this->textureSelector->update(this->mousePosWindow);
    }

    if (!this->textureSelector->isActive()) {
        this->previewTexture.setPosition(this->mousePosGrid.x * this->stateData.gridSize,
                                       this->mousePosGrid.y * this->stateData.gridSize);
        this->previewTexture.setTextureRect(this->tilemap->getTextureRect());
    }

    std::stringstream ss;
    this->cursorText.setPosition(this->mousePosView.x + 20, this->mousePosView.y - 20);
    ss << this->mousePosView.x << " x " << this->mousePosView.y << "\n"
       << this->mousePosGrid.x << this->mousePosGrid.y << "\n"
       << this->tilemap->getTextureRect().left << this->tilemap->getTextureRect().top << "\n";
    this->cursorText.setString(ss.str());
}

void EditorState::renderGui(sf::RenderTarget *target) {
    this->tilemap->render(*target);
    if(this->showTextureSelector) {
        this->textureSelector->render(*target);
    }
}

void EditorState::initTexts() {
    this->cursorText.setFont(*this->stateData.font);
    this->cursorText.setCharacterSize(12);
    this->cursorText.setFillColor(sf::Color::White);
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 20);
}
