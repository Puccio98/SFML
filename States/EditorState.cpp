#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                         std::stack<State *> *states) : State(window,
                                                              supportedKeys, states) {
    this->initFonts();
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
    State::update(dt);
    this->updateMousePositions();
    this->updateButtons();
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    this->renderButtons(target);
}

void EditorState::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
    };
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
}

//Initializer Functions
void EditorState::initVariables() {

}

void EditorState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }
}
