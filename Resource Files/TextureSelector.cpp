#include "TextureSelector.h"
#include "DropDownList.h"

//TEXTURE SELECTOR
TextureSelector::TextureSelector(float x, float y, float width, float height, const sf::Texture& texture_sheet) {
    this->bounds.setSize(sf::Vector2f(width, height));
    this->bounds.setPosition(x, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    this->sheet.setTexture(texture_sheet);
    this->sheet.setPosition(x, y);

    if(this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width ||
        this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
    {
        this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }
}

TextureSelector::~TextureSelector() {

}

void TextureSelector::render(sf::RenderTarget& target) {
    target.draw(this->bounds);
    target.draw(this->sheet);
}

void TextureSelector::update() {

}
