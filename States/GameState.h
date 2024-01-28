#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include "State.h"

class GameState : public State {
private:
    Player *player{};

    void initTextures();

    void initPlayer();

public:
    GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~GameState();

    //Functions
    void updateInput(const float &dt) override;

    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;
};

#endif //SFML_GAMESTATE_H
