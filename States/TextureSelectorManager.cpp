#include <Graphics/Font.hpp>
#include "../Gui/TextureSelector.h"

struct TextureSelectorManager {
    TextureSelector *selector;
    std::string buttonKey;
    sf::Texture texture;
    std::string texturePath;

    TextureSelectorManager(const std::string &buttonKey, const std::string &texturePath)
            : selector(nullptr), buttonKey(buttonKey), texturePath(texturePath) {}

    void init(float offsetX, float offsetY, float gridSize, sf::Font &font) {
        texture.loadFromFile(texturePath);
        selector = new TextureSelector(offsetX, offsetY, gridSize, texture);
    }

    void update(const sf::Vector2f &mousePos) {
        if (selector && selector->isActive()) {
            selector->update(mousePos);
        }
    }

    void render(sf::RenderTarget *target) {
        if (selector && selector->isActive() && !selector->isTimerOver()) {
            selector->render(*target);
        }
    }

    bool isActive() const {
        return selector && selector->isActive();
    }

    void restartTimer() {
        if (selector) selector->restartTimer();
    }

    ~TextureSelectorManager() {
        delete selector;
    }
};
