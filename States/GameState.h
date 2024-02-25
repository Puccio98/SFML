#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include "PauseMenuState.h"
#include "../Map/TileMap.h"

class GameState : public State {
private:
    Player *player{};
    PauseMenuState pauseMenuState;
    Tilemap map;

    void initTextures();

    void initPlayer();

public:
    explicit GameState(StateData &stateData);

    virtual ~GameState();

    //Functions
    void updateInput(const float &dt);

    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isQuit() const override;

};

#endif //SFML_GAMESTATE_H
