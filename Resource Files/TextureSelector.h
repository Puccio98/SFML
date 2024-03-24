#ifndef SFML_TEXTURESELECTOR_H
#define SFML_TEXTURESELECTOR_H


#include <Graphics/RectangleShape.hpp>
#include <Graphics/Sprite.hpp>

class TextureSelector {
private:
    sf::RectangleShape bounds;
    sf::Sprite sheet;
    sf::RectangleShape selector;
    sf::RectangleShape selected;
    sf::Vector2u mousePosGrid;
    float gridSize;
    bool active;

public:
    TextureSelector(float x, float y, float gridSize, const sf::Texture &texture_sheet);

    virtual ~TextureSelector();

    void update(sf::Vector2i mousePosWindow);

    void render(sf::RenderTarget &target);

    bool isActive() const;

    const sf::Vector2u &getMousePosGrid() const;

    void setSelectedTile(const sf::Vector2u &posGrid);

    void setSelectedTile();

    const sf::RectangleShape &getSelected() const;
};


#endif //SFML_TEXTURESELECTOR_H
