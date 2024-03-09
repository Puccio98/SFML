#ifndef SFML_TEXTURESELECTOR_H
#define SFML_TEXTURESELECTOR_H


#include <Graphics/RectangleShape.hpp>
#include <Graphics/Sprite.hpp>

class TextureSelector {
private:
    sf::RectangleShape bounds;
    sf::Sprite sheet;

public:
    TextureSelector(float x, float y, float width, float height, const sf::Texture& texture_sheet);
    virtual ~TextureSelector();

    void update();
    void render(sf::RenderTarget& target);
};


#endif //SFML_TEXTURESELECTOR_H
