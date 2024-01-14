#ifndef SFML_STATE_H
#define SFML_STATE_H

#include "../Entities/Player.h"

class State {
private:
    void debugMousePosition();

protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    bool quit;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds() = 0;

public:
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);

    virtual ~State();

    const bool& getQuit() const;

    virtual void endState();
    virtual void updateMousePositions();
    virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};

#endif //SFML_STATE_H
