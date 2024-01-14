#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include "State.h"

class GameState : public State {
private:
    Player* player;
    void initTextures();
    void initKeybinds() override;
    void initPlayers();
public:
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updateInput(const float& dt) override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};

#endif //SFML_GAMESTATE_H
