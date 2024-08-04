#ifndef SFML_EDITORSTATE_H
#define SFML_EDITORSTATE_H

#include "State.h"
#include "PauseMenuState.h"
#include "../Gui/TextureSelector.h"
#include "../Gui/Button.h"
#include "../Map/Tilemap.h"
#include "../Gui/TextureSelector.h"
#include "../Gui/Sidebar.h"

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
    Tilemap *tileMap;
    sf::RectangleShape previewTexture;
    bool showTextureSelector;
    sf::Time textureSelectorTimer = sf::seconds(5);
    sf::Clock clock;
    GUI::Sidebar *sideBar;
    std::string tileTexturePath;
    TextureSelector *textureSelector;
    sf::View view;
    float cameraSpeed;
    std::vector<SidebarButton> buttonsKeyLabel;

    std::vector<TILE_BEHAVIOURS> tileTypes;

    // Define a simple Point struct to hold x and y coordinates
    struct Point {
        int x, y;

        // Custom comparison operator for std::map to work correctly
        bool operator<(const Point &other) const {
            return std::tie(x, y) < std::tie(other.x, other.y);
        }
    };

// Define the map
    std::map<Point, bool> positionMap;

    //Functions
    void initVariables();

    void initView();

    void initButtonsKeyLabel();

    void updateSidebar(float dt);

    void updateGui();

    void renderGui(sf::RenderTarget *target);

    void initGui();

    void openTextureSelector();

    void updateInput(const float &dt);

    void updateView(const float &dt);

    void setAllToFalse() {
        for (auto &pair: positionMap) {
            pair.second = false;
        }
    }

    void addTile(TILE_TYPES type);

    void addTexture();

    /**
     * Seleziona la tile in base alla posizione del mouse e resetta il clock.
     * @param mousePosWindow
     */
    void setSelectedTile(sf::Vector2f &mousePos);

    /**
     * Seleziona la tile prendendo una direzione e resetta il clock.
     * @param dir_x
     * @param dir_y
     */
    void setSelectedTile(int dir_x, int dir_y);
};


#endif //SFML_EDITORSTATE_H
