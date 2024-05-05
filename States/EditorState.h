#ifndef SFML_EDITORSTATE_H
#define SFML_EDITORSTATE_H

#include "State.h"
#include "PauseMenuState.h"
#include "../ResourceFiles/TextureSelector.h"
#include "../ResourceFiles/Button.h"
#include "../Map/Tilemap.h"
#include "../ResourceFiles/TextureSelector.h"

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
    Tilemap *tileMap;
    sf::RectangleShape previewTexture;
    bool showTextureSelector;
    sf::Time textureSelectorTimer = sf::seconds(5);
    sf::Clock clock;
    sf::RectangleShape sideBar;
    std::string tileTexturePath;
    TextureSelector *textureSelector;
    sf::View view;
    float cameraSpeed;

    std::vector<TILE_TYPES> tileTypes;

    //Functions
    void initVariables();

    void initView();

    void initButtons();

    void updateButtons();

    void updateGui();

    void renderButtons(sf::RenderTarget *target);

    void renderGui(sf::RenderTarget *target);

    void initGui();

    void openTextureSelector();

    void updateInput(const float &dt);

    void updateView(const float &dt);
};


#endif //SFML_EDITORSTATE_H
