#include "TextureSelector.h"
#include "DropDownList.h"

//TEXTURE SELECTOR
TextureSelector::TextureSelector(float x, float y, float gridSize, const sf::Texture &texture_sheet) {
    this->active = false;
    this->gridSize = gridSize;
    this->bounds.setSize(
            sf::Vector2f(static_cast<float>(texture_sheet.getSize().x), static_cast<float>(texture_sheet.getSize().y)));
    this->bounds.setPosition(x, y);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    this->sheet.setTexture(texture_sheet);
    this->sheet.setPosition(x, y);

    if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width ||
        this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height) {
        this->sheet.setTextureRect(
                sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }
    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(this->gridSize, this->gridSize));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::Yellow);

    this->selected.setPosition(x, y);
    this->selected.setSize(sf::Vector2f(this->gridSize, this->gridSize));
    this->selected.setFillColor(sf::Color::Transparent);
    this->selected.setOutlineThickness(1.f);
    this->selected.setOutlineColor(sf::Color::Blue);
}

TextureSelector::~TextureSelector() {

}

void TextureSelector::render(sf::RenderTarget &target) {
    target.draw(this->bounds);
    target.draw(this->sheet);
    if (this->active) {
        target.draw(this->selector);
    }
    target.draw(this->selected);
}


void TextureSelector::update(const sf::Vector2i mousePosWindow) {
    this->active = this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow));

    if (this->active) {
        this->mousePosGrid.x = (mousePosWindow.x -
                                static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(gridSize);
        this->mousePosGrid.y = (mousePosWindow.y -
                                static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(gridSize);

        this->selector.setPosition(mousePosGrid.x * gridSize, mousePosGrid.y * gridSize);
    }
}

bool TextureSelector::isActive() const {
    return active;
}

const sf::Vector2u &TextureSelector::getMousePosGrid() const {
    return mousePosGrid;
}

void TextureSelector::setSelectedTile(const sf::Vector2u &posGrid) {
    this->selected.setPosition(posGrid.x * gridSize, posGrid.y * gridSize);
}

void TextureSelector::setSelectedTile() {
    int originalHorizontalPosition = this->selected.getPosition().x / gridSize;
    int originalVerticalPosition = this->selected.getPosition().y / gridSize;
    int lastHorizontalPosition = this->bounds.getSize().x / gridSize;
    int lastVerticalPosition = this->bounds.getSize().y / gridSize;
    int nextHorizontalPosition = (originalHorizontalPosition + 1) % lastHorizontalPosition;
    if (nextHorizontalPosition == 0) {
        int nextVerticalPosition = (originalVerticalPosition + 1) % lastVerticalPosition;
        this->selected.setPosition(this->selected.getPosition().x, nextVerticalPosition * gridSize);
    }
    this->selected.setPosition(nextHorizontalPosition * gridSize, this->selected.getPosition().y);
}

const sf::RectangleShape &TextureSelector::getSelected() const {
    return this->selected;
}

