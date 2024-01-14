#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window,
                                                                  supportedKeys, states) {
    this->initFonts();
    this->initVariables();
    EditorState::initKeybinds();
    this->initButtons();

}

EditorState::~EditorState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
}

void EditorState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds["CLOSE"])))
        this->endState();
}

void EditorState::update(const float &dt) {
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    this->renderButtons(target);
}

void EditorState::initKeybinds() {
    std::ifstream ifs("Config/editorstate_keybinds.ini");

    if (ifs.is_open()) {
        std::string key;
        std::string key_value;
        while (ifs >> key >> key_value) {
            this->keybinds[key] = this->supportedKeys->at(key_value);
        }
    }

    ifs.close();
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
