#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture &texture, const sf::Vector2f &tileTexturePosition,
           const std::vector<TILE_TYPES> &tileTypes) {
    this->tileTypes.insert(this->tileTypes.end(), tileTypes.begin(), tileTypes.end());
    this->initShapes();
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    //Se collision, bordo rosso
    if (this->isOfType(TILE_TYPES::COLLISION)) {
        this->shapes.setOutlineColor(sf::Color(255, 0, 0, 150));
        this->shapes.setOutlineThickness(-2);
    }
    target.draw(this->shapes);
}

void Tile::update() {

}

std::string Tile::getAsString(unsigned x, unsigned y, unsigned z) const {
    std::stringstream ss;
    ss << "p " << x << " " << y << " " << z
       << " t_p " << this->getSpritesAsString()
       << " t_t " << this->getTypesAsString();
    return ss.str();
}

std::string Tile::getTypesAsString() const {
    std::string s;
    for (TILE_TYPES i: tileTypes) {
        s.append(std::to_string(static_cast<int>(i)) + " ");
    }

    return s;
}

bool Tile::isOfType(TILE_TYPES type) {
    return std::find(this->tileTypes.begin(), this->tileTypes.end(), type) != tileTypes.end();
}

std::string Tile::getSpritesAsString() const {
    std::string s;
    return s.append(
            std::to_string(this->shapes.getTextureRect().left) + " " + std::to_string(this->shapes.getTextureRect().top));
}

void Tile::initShapes() {
    sf::RectangleShape texture;
    texture.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    texture.setPosition(x, y);
    texture.setTexture(&texture);
    texture.setTextureRect(sf::IntRect(tileTexturePosition.x, tileTexturePosition.y, gridSizeF, gridSizeF));
    this->shapes.push_back()

}
