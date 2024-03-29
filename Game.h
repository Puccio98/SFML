#ifndef SFML_GAME_H
#define SFML_GAME_H

#include "States/MainMenuState.h"

class Game {
private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    bool fullscreen;
    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;
    sf::ContextSettings windowSettings;
    std::map<std::string, int> supportedKeys;

    //Initialization
    void initVariables();
    void initWindow();
    void initState();
    void initKeys();

public:
    Game();

    virtual ~Game();

    //Functions
    //Regular
    void endApplication();

    //Update
    void updateDT();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();
};


#endif //SFML_GAME_H
