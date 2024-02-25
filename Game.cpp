#include "Game.h"

//Static Functions

//Initializer functions
void Game::initWindow() {
    if (this->graphicsSettings->fullscreen)
        this->window = new sf::RenderWindow(this->graphicsSettings->resolution, this->graphicsSettings->title,
                                            sf::Style::Fullscreen, this->graphicsSettings->contextSettings);
    else
        this->window = new sf::RenderWindow(this->graphicsSettings->resolution, this->graphicsSettings->title,
                                            sf::Style::Titlebar | sf::Style::Close,
                                            this->graphicsSettings->contextSettings);

    this->window->setFramerateLimit(this->graphicsSettings->frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicsSettings->verticalSync);
    this->window->setKeyRepeatEnabled(false);
}

//Constructors/Destructors
Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initKeys();
    this->initFonts();
    this->stateData = new State::StateData(&states, this->window, &this->supportedKeys, &font, graphicsSettings);
    this->initState();
}

Game::~Game() {
    delete this->window;
    delete this->graphicsSettings;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }

    delete stateData;
}

//Functions
void Game::update() {
    if (this->states.empty()) {
        Game::endApplication();
        this->window->close();
    }

    this->states.top()->update(this->dt);
    if (this->states.top()->isQuit()) {
        this->states.top()->endState();

        delete this->states.top();
        this->states.pop();
    }
}

void Game::render() {
    this->window->clear();
    //Render Items
    if (!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->updateDT();
        this->update();
        this->render();
    }
}

void Game::updateDT() {
    /*Update the dt variable with the time it takes to play and render one frame */
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::initState() {
    this->states.push(new MainMenuState(*stateData));
}

void Game::endApplication() {
    std::cout << "ending application!";
}

void Game::initKeys() {
    std::ifstream ifs("Config/supported_keys.ini");

    if (ifs.is_open()) {
        std::string key;
        int key_value = 0;
        while (ifs >> key >> key_value) {
            this->supportedKeys[key] = key_value;
        }
    }

    ifs.close();
}

void Game::initVariables() {
    this->window = nullptr;
    this->graphicsSettings = nullptr;
    this->dt = 0.f;
}

void Game::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::GAME::COULD NOT LOAD FONT");
    };
}

void Game::initGraphicsSettings() {
    this->graphicsSettings = new GraphicsSettings(this->graphicsSettingsFilePath);
    this->graphicsSettings->load();
}
