#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include "PauseMenuState.h"
#include "../Map/TileMap.h"

class GameState : public State {
private:
    Player *player{};
    PauseMenuState pauseMenuState;
    Tilemap *tilemap;
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    void initTextures();

    void initPlayer();

public:
    explicit GameState(StateData &stateData);

    virtual ~GameState();

    //Functions
    void initView();

    void updateView(const float &dt);

    void updateInput(const float &dt);

    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isQuit() const override;

    void initTilemap();

};

#endif //SFML_GAMESTATE_H
