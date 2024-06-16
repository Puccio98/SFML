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
        sf::Vector2i gridPosition = getGridPosition(mousePosWindow);
        const sf::Vector2f position = sf::Vector2f((gridPosition.x * gridSize) + bounds.getPosition().x,
                                                   (gridPosition.y *
                                                    gridSize) + bounds.getPosition().y);
        this->selector.setPosition(position);
    }
}

sf::Vector2i TextureSelector::getGridPosition(const sf::Vector2i &absolutePosition) {
    float relativeX = absolutePosition.x - bounds.getPosition().x;
    float relativeY = absolutePosition.y - bounds.getPosition().y;

    int gridX = static_cast<int>(relativeX / gridSize);
    int gridY = static_cast<int>(relativeY / gridSize);

    return {gridX, gridY};
}

bool TextureSelector::isActive() const {
    return active;
}

void TextureSelector::setSelectedTile(sf::Vector2i &mousePosWindow) {
    sf::Vector2i gridPosition = getGridPosition(mousePosWindow);
    const sf::Vector2f position = sf::Vector2f((gridPosition.x * gridSize) + bounds.getPosition().x, (gridPosition.y *
                                                                                                      gridSize) +
                                                                                                     bounds.getPosition().y);
    this->selected.setPosition(position);
}

void TextureSelector::setSelectedTile(int dir_x, int dir_y) {
    float relativeX = this->selected.getPosition().x - bounds.getPosition().x;
    float relativeY = this->selected.getPosition().y - bounds.getPosition().y;

    int originalHorizontalPosition = static_cast<int>(relativeX / gridSize);
    int originalVerticalPosition = static_cast<int>(relativeY / gridSize);

    int horizontalBound = this->bounds.getSize().x / gridSize;
    int verticalBound = this->bounds.getSize().y / gridSize;
    int nextHorizontalPosition = (originalHorizontalPosition + dir_x >= horizontalBound ||
                                  originalHorizontalPosition + dir_x < 0) ?
                                 originalHorizontalPosition : (originalHorizontalPosition + dir_x);
    int nextVerticalPosition = (originalVerticalPosition + dir_y >= verticalBound ||
                                originalVerticalPosition + dir_y < 0) ?
                               originalVerticalPosition : (originalVerticalPosition + dir_y);


    this->selected.setPosition((nextHorizontalPosition * gridSize) + this->bounds.getPosition().x,
                               (nextVerticalPosition * gridSize) + this->bounds.getPosition().y);
}

const sf::RectangleShape &TextureSelector::getSelected() const {
    return this->selected;
}

sf::Vector2f TextureSelector::getSelectedRelativePosition() {
    return sf::Vector2f(this->selected.getPosition().x - this->bounds.getPosition().x,
                        this->selected.getPosition().y - this->bounds.getPosition().y);
}

