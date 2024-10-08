#ifndef SFML_GAMESTATE_H
#define SFML_GAMESTATE_H

#include "PauseMenuState.h"
#include "../Map/Tilemap.h"
#include "../Gui/PlayerGUI.h"
#include "../Entities/Enemies/Enemy.h"
#include <cmath>

class GameState : public State {
private:
    Player *player{};
    std::vector<Enemy *> enemies;
    PauseMenuState pauseMenuState;
    Tilemap *tilemap;
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    GUI::PlayerGUI *playerGUI;

    void initTextures();

    void initPlayer();

    void initPlayerGUI(Player *_player);

public:
    explicit GameState(StateData &stateData);

    virtual ~GameState();

    //Functions
    void initView();

    void updateView(const float &dt);

    void updateInput(const float &dt);

    void updateEntity(const float &dt, Entity &entity);

    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isQuit() const override;

    void initTilemap();

    void updateEnemies(const float &dt);

    void renderEnemies(int layerIndex, sf::RenderTarget *target = nullptr);
};

#endif //SFML_GAMESTATE_H
