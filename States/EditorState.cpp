#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                         std::stack<State *> *states, sf::Font &font) :
        State(window, supportedKeys, states, font),
        pauseMenuState(PauseMenuState(window, supportedKeys, font)) {
    this->initVariables();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();

}

EditorState::~EditorState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
}

void EditorState::update(const float &dt) {
    if (!pauseMenuState.isPaused()) {
        State::update(dt);
        this->updateMousePositions();
        this->updateButtons();
    } else {
        pauseMenuState.update(dt);
    }
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    this->renderButtons(target);
    this->map.render(*target);


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

    this->map.update();
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
