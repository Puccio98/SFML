#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture &texture, sf::Vector2f &tileTexturePosition,
           std::vector<TILE_TYPES>& tileTypes) {
    this->tileTypes.insert(this->tileTypes.end(), tileTypes.begin(), tileTypes.end());
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(sf::IntRect(tileTexturePosition.x, tileTexturePosition.y, gridSizeF, gridSizeF));
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

void Tile::update() {

}

std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << false << " "
       << (int) TILE_TYPES::DEFAULT;
    return ss.str();
}

std::string Tile::getTypesAsString() {
    std::string s = "";
    for(TILE_TYPES i : tileTypes){
        s.append(std::to_string(static_cast<int>(i)) + " ");
    }

    return s;
}
