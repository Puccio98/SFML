#ifndef SFML_STATE_H
#define SFML_STATE_H

#include "../Entities/Player.h"
#include "../Settings/GraphicsSettings.h"

class State {


private:
    __attribute__((unused)) void debugMousePosition() const;


public:
    struct StateData {
        StateData(std::stack<State *> *_states, sf::RenderWindow *_window,
                  std::map<std::string, int> *_supportedKeys,
                  sf::Font *_font, GraphicsSettings *_graphicsSettings) : states(_states), window(_window),
                                                                          supportedKeys(_supportedKeys),
                                                                          font(_font),
                                                                          graphicsSettings(_graphicsSettings) {};

        std::stack<State *> *states;
        sf::RenderWindow *window;
        std::map<std::string, int> *supportedKeys;
        sf::Font *font;
        GraphicsSettings *graphicsSettings;
    };

    explicit State(StateData &stateData);


    virtual ~State();

    virtual bool isQuit() const;

    virtual void endState();

    virtual void updateMousePositions();

    virtual void update(const float &dt);

    virtual void render(sf::RenderTarget *target) = 0;

    virtual void handleEvent(sf::Event &event, const float &dt) = 0;

    void pollEvents(const float &dt);

protected:
    std::map<std::string, int> keybinds;
    bool quit;
    StateData &stateData;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Resources
    std::map<std::string, sf::Texture> textures;

    //Functions
    virtual void initKeybinds(std::string keybindsFilePath);
};


#endif //SFML_STATE_H

