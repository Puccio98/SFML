#ifndef SFML_GAME_H
#define SFML_GAME_H

#include "States/MainMenuState.h"


class Game {
private:
    //Variables
    sf::RenderWindow *window;
    GraphicsSettings *graphicsSettings;
    sf::Clock dtClock;
    float dt;

    std::string graphicsSettingsFilePath = "Config/graphics.ini";
    std::stack<State *> states;
    sf::Font font;
    std::map<std::string, int> supportedKeys;

    //Initialization
    void initVariables();

    void initGraphicsSettings();

    void initWindow();

    void initState();

    void initKeys();

    void initFonts();

public:
    Game();

    virtual ~Game();

    //Functions
    //Regular
    static void endApplication();

    //Update
    void updateDT();

    void update();

    //Render
    void render();

    //Core
    void run();
};


#endif //SFML_GAME_H
