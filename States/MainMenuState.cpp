

#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys,
                             std::stack<State *> *states) : State(window,
                                                                  supportedKeys, states) {
    this->initFonts();
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

void MainMenuState::updateInput(const float &dt) {

}

void MainMenuState::update(const float &dt) {
    State::update(dt);
    this->updateMousePositions();
    this->updateInput(dt);
    this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    target->draw(this->background);
    this->renderButtons(*target);
}

void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    };
}

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font, "New Game", 50,
                                             sf::Color(120, 50, 80, 200),
                                             sf::Color(150, 50, 80, 250),
                                             sf::Color(90, 40, 60, 50),
                                             sf::Color(120, 50, 80, 0),
                                             sf::Color(150, 50, 80, 0),
                                             sf::Color(90, 40, 60, 0));

    this->buttons["SETTING_STATE"] = new Button(100, 200, 150, 50, &this->font, "Settings", 50,
                                                sf::Color(120, 50, 80, 200),
                                                sf::Color(150, 50, 80, 250),
                                                sf::Color(90, 40, 60, 50),
                                                sf::Color(120, 50, 80, 0),
                                                sf::Color(150, 50, 80, 0),
                                                sf::Color(90, 40, 60, 0));

    this->buttons["EDITOR_STATE"] = new Button(100, 300, 150, 50, &this->font, "Editor", 50,
                                               sf::Color(120, 50, 80, 200),
                                               sf::Color(150, 50, 80, 250),
                                               sf::Color(90, 40, 60, 50),
                                               sf::Color(120, 50, 80, 0),
                                               sf::Color(150, 50, 80, 0),
                                               sf::Color(90, 40, 60, 0));

    this->buttons["CLOSE"] = new Button(100, 400, 150, 50, &this->font, "Close Game", 50,
                                        sf::Color(120, 50, 80, 200),
                                        sf::Color(150, 50, 80, 250),
                                        sf::Color(90, 40, 60, 50),
                                        sf::Color(120, 50, 80, 0),
                                        sf::Color(150, 50, 80, 0),
                                        sf::Color(90, 40, 60, 0));
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
    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }


    //New Game
    if (this->buttons["SETTING_STATE"]->isPressed()) {
        this->states->push(new SettingsState(this->window, this->supportedKeys, this->states));
    }

    //Editor
    if (this->buttons["EDITOR_STATE"]->isPressed()) {
        this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
    }

    //Exit Game
    if (this->buttons["CLOSE"]->isPressed()) {
        this->quit = true;
    }
}

//Initializer Functions
void MainMenuState::initBackground() {
    this->background.setSize(
            sf::Vector2f(static_cast<float>(this->window->getSize().x),
                         static_cast<float>(this->window->getSize().y))
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
}
