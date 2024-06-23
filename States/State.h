#ifndef SFML_STATE_H
#define SFML_STATE_H

#include "../Entities/Player.h"
#include "../Settings/GraphicsSettings.h"
#include "StateData.h"
#include "../enums/view_types.cpp"

class StateData;

class State {
private:
    __attribute__((unused)) void debugMousePosition() const;


public:

    explicit State(StateData &stateData);

    virtual ~State();

    virtual bool isQuit() const;

    virtual void endState();

    void updateMousePositions(const sf::View &view);

    virtual void update(const float &dt);

    virtual void update(const float &dt, const sf::View &_view);

    virtual void render(sf::RenderTarget *target) = 0;

    virtual void handleEvent(sf::Event &event, const float &dt) = 0;

    void pollEvents(const float &dt);

    float p2px(float percentage);

    float p2py(float percentage);

protected:
    std::map<std::string, int> keybinds;
    bool quit;
    StateData &stateData;

    sf::Text mouseDebug;
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;


    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds(std::string keybindsFilePath);

    void updateMouseDebug();

    sf::Vector2i getPosGrid(VIEW_TYPES viewType) const;

    void initMouseDebug();
};


#endif //SFML_STATE_H

