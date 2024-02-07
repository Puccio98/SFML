#ifndef SFML_EDITORSTATE_H
#define SFML_EDITORSTATE_H

#include "State.h"
#include "../Resource Files/Button.h"

class EditorState : public State {
public:
    EditorState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);

    virtual ~EditorState();

    //Functions
    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

private:
    //Variables
    sf::Font font;
    std::map<std::string, GUI::Button *> buttons;

    //Functions
    void initVariables();

    void initFonts();

    void initButtons();

    void updateButtons();

    void renderButtons(sf::RenderTarget *target);

public:
    void handleEvent(sf::Event &event, const float &dt) override;
};


#endif //SFML_EDITORSTATE_H
