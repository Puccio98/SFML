//
// Created by malte on 19/01/2024.
//

#include "Tile.h"

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture) {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    //this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(x, y);
    this->shape.setTexture(&texture);
    this->shape.setOutlineColor(sf::Color::Black);
    this->shape.setOutlineThickness(1.f);
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}

void Tile::update() {

}
