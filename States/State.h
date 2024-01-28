#ifndef SFML_STATE_H
#define SFML_STATE_H

#include "../Entities/Player.h"

class State {
private:
    __attribute__((unused)) void debugMousePosition() const;

protected:
    std::stack<State *> *states;
    sf::RenderWindow *window;
    bool quit;
    std::map<std::string, int> *supportedKeys;
    std::map<std::string, int> keybinds;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds(std::string keybindsFilePath);


public:
    State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~State();

    virtual bool isQuit() const;

    virtual void endState();

    virtual void updateMousePositions();

    virtual void updateInput(const float &dt) = 0;

    virtual void update(const float &dt);

    virtual void render(sf::RenderTarget *target) = 0;

    virtual void handleEvent(sf::Event &event, const float &dt) = 0;

    void pollEvents(const float &dt);
};

#endif //SFML_STATE_H
