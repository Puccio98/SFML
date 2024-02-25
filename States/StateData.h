#include <stack>
#include "State.h"

class State;

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
