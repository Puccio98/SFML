#ifndef SFML_EDITORSTATE_H
#define SFML_EDITORSTATE_H

#include "State.h"
#include "PauseMenuState.h"
#include "../Resource Files/Button.h"
#include "../Map/Tilemap.h"

class EditorState : public State {
public:
    EditorState(StateData &stateData);

    virtual ~EditorState();

    //Functions
    void update(const float &dt) override;

    void render(sf::RenderTarget *target) override;

    void handleEvent(sf::Event &event, const float &dt) override;

    bool isQuit() const override;

private:
    //Variables
    PauseMenuState pauseMenuState;
    std::map<std::string, GUI::Button *> buttons;
    Tilemap map;

    //Functions
    void initVariables();

    void initButtons();

    void updateButtons();

    void renderButtons(sf::RenderTarget *target);

};


#endif //SFML_EDITORSTATE_H
