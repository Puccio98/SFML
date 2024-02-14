#include "Game.h"

//Static Functions

//Initializer functions
void Game::initWindow() {
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    sf::VideoMode window_bounds(sf::VideoMode::getDesktopMode());
    fullscreen = false;
    std::string title = "None";
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> fullscreen;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();
    windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close,
                                            windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
    this->window->setKeyRepeatEnabled(false);

}

//Constructors/Destructors
Game::Game() {
    this->initVariables();
    this->initWindow();
    this->initKeys();
    this->initFonts();
    this->initState();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
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
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &states, font));
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
    this->dt = 0.f;
    this->fullscreen = false;
}

void Game::initFonts() {
    if (!this->font.loadFromFile("../Fonts/Roboto-Black.ttf")) {
        throw ("ERROR::GAME::COULD NOT LOAD FONT");
    };
}