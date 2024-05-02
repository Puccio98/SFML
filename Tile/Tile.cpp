#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture &texture, const sf::Vector2f &tileTexturePosition,
           const std::vector<TILE_TYPES> &tileTypes) {
    this->tileTypes.insert(this->tileTypes.end(), tileTypes.begin(), tileTypes.end());
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(sf::IntRect(tileTexturePosition.x, tileTexturePosition.y, gridSizeF, gridSizeF));
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    //Se collision, bordo rosso
    if(std::find(this->tileTypes.begin(), this->tileTypes.end(), TILE_TYPES::COLLISION) != tileTypes.end()) {
        this->shape.setOutlineColor(sf::Color(255, 0,0,150));
        this->shape.setOutlineThickness(-2);
    }
    target.draw(this->shape);
}

void Tile::update() {

}

std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
       << this->getTypesAsString();
    return ss.str();
}

std::string Tile::getTypesAsString() const {
    std::string s;
    for (TILE_TYPES i: tileTypes) {
        s.append(std::to_string(static_cast<int>(i)) + " ");
    }

    return s;
}
