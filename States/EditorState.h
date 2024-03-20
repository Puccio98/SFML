#ifndef SFML_EDITORSTATE_H
#define SFML_EDITORSTATE_H

#include "State.h"
#include "PauseMenuState.h"
#include "../Resource Files/TextureSelector.h"
#include "../Resource Files/Button.h"
#include "../Map/Tilemap.h"
#include "../Resource Files/TextureSelector.h"

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
    Tilemap *tilemap;
    sf::RectangleShape previewTexture;
    sf::Text cursorText;
    bool showTextureSelector;

    TextureSelector *textureSelector;

    //Functions
    void initVariables();

    void initButtons();

    void initTexts();

    void updateButtons();

    void updateGui();

    void renderButtons(sf::RenderTarget *target);

    void renderGui(sf::RenderTarget *target);

    void initTileMap();

    void initGui();
};


#endif //SFML_EDITORSTATE_H
