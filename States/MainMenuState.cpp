

#include "MainMenuState.h"
#include "../Gui/PushButton.h"
#include "../Gui/Utils.h"

MainMenuState::MainMenuState(StateData &stateData) : State(stateData) {
    this->initVariables();
    this->initBackground();
    State::initKeybinds("Config/menustate_keybinds.ini");
    this->initButtons();
}

MainMenuState::~MainMenuState() {
    for (auto &button: this->buttons) {
        delete button.second;
    }
}

void MainMenuState::update(const float &dt) {
    State::update(dt);
    this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->stateData.window;
    target->draw(this->background);
    this->renderButtons(*target);
}

void MainMenuState::initButtons() {
    auto createButton = [&](const std::string &key, const std::string &label, int yMultiplier) {
        float x = GUI::Utils::p2px(5, this->dvm);
        float y = GUI::Utils::p2py(5 + (12 * yMultiplier), this->dvm);
        float width = GUI::Utils::p2px(15, this->dvm);
        float height = GUI::Utils::p2py(7, this->dvm);

        this->buttons[key] = new GUI::PushButton(x, y, width, height, this->stateData.font, label,
                                                 GUI::Utils::charSize(this->dvm),
                                                 CssColor::ClassicText(), CssColor::ClassicButton());
    };

    createButton("GAME_STATE", "New Game", 0);
    createButton("SETTING_STATE", "Settings", 1);
    createButton("EDITOR_STATE", "Editor", 2);
    createButton("CLOSE", "Close Game", 3);
}


void MainMenuState::renderButtons(sf::RenderTarget &target) {
    for (auto &button: this->buttons) {
        button.second->render(target);
    }
}

void MainMenuState::updateButtons() {
    /*Updates all buttons in state and handles their functionality*/
    for (auto &button: this->buttons) {
        button.second->update(this->mousePosView);
    }

    //New Game
    if (this->buttons["GAME_STATE"]->isClicked()) {
        this->stateData.states->push(new GameState(this->stateData));
    }


    //Setting State
    if (this->buttons["SETTING_STATE"]->isClicked()) {
        this->stateData.states->push(new SettingsState(this->stateData));
    }

    //Editor
    if (this->buttons["EDITOR_STATE"]->isClicked()) {
        this->stateData.states->push(new EditorState(this->stateData));
    }

    //Exit Game
    if (this->buttons["CLOSE"]->isClicked()) {
        this->quit = true;
    }
}

//Initializer Functions
void MainMenuState::initBackground() {
    this->background.setSize(
            sf::Vector2f(static_cast<float>(this->dvm.width),
                         static_cast<float>(this->dvm.height))
    );
    if (!this->backgroundTexture.loadFromFile("../Resources/images/background.png")) {
        throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
    };
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initVariables() {

}


void MainMenuState::handleEvent(sf::Event &event, const float &dt) {
    if (event.type == sf::Event::KeyPressed && event.key.code == this->keybinds["CLOSE"]) {
        this->endState();
    }

    for (auto &button: this->buttons) {
        button.second->handleEvent(event, mousePosView);
    }
}
