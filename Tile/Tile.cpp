//
// Created by malte on 19/01/2024.
//

#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture, const sf::IntRect &texture_rect) {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    //this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(1.f);
    this->shape.setTextureRect(texture_rect);
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

void Tile::update() {

}
