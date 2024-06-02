#include "Tile.h"

Tile::Tile(const TileData &tileData, sf::Texture &texture,
           const std::vector<sf::Vector2f> &texturePositions,
           const std::vector<TILE_TYPES> &tileTypes, sf::Font &font) : layer(tileData.index_z) {
    this->initLayerText(tileData.index_x * tileData.gridSize, tileData.index_y * tileData.gridSize, font);
    this->tileTypes.insert(this->tileTypes.end(), tileTypes.begin(), tileTypes.end());
    this->initShapes(tileData.index_x * tileData.gridSize, tileData.index_y * tileData.gridSize, tileData.gridSize,
                     texture, texturePositions);
}

Tile::~Tile() {

}

void Tile::render(sf::RenderTarget &target) {
    if (sprites.empty()) {
        target.draw(defaultSprite);
        target.draw(this->layerText);
    }

    for (std::size_t i = 0; i < this->sprites.size(); ++i) {
        sf::RectangleShape &sprite = this->sprites[i];

        //Se collision, bordo rosso
        if (this->isOfType(TILE_TYPES::COLLISION)) {
            sprite.setOutlineColor(sf::Color(255, 0, 0, 150));
            sprite.setOutlineThickness(-2);
        }

        target.draw(sprite);

        if (i == this->sprites.size() - 1) {
            target.draw(this->layerText);
        }
    }

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

    for (const sf::RectangleShape &sprite: this->sprites) {
        s.append(
                std::to_string(sprite.getTextureRect().left) + " " + std::to_string(sprite.getTextureRect().top)
        );
    }
    return s;
}

void Tile::initShapes(float x, float y, float gridSizeF, sf::Texture &textureSheet,
                      const std::vector<sf::Vector2f> &texturePositions) {
    if (texturePositions.empty()) {
        defaultSprite.setSize(sf::Vector2f(gridSizeF, gridSizeF));
        defaultSprite.setPosition(x, y);
        defaultSprite.setFillColor(this->setGreyColor(layer, 30.f));
    }

    for (sf::Vector2f texturePosition: texturePositions) {
        sf::RectangleShape texture;
        texture.setSize(sf::Vector2f(gridSizeF, gridSizeF));
        texture.setPosition(x, y);
        texture.setTexture(&textureSheet);
        texture.setTextureRect(sf::IntRect(texturePosition.x, texturePosition.y, gridSizeF, gridSizeF));
        this->sprites.push_back(texture);
    }
}

void Tile::initLayerText(float x, float y, sf::Font &font) {
    this->layerText.setFont(font);
    this->layerText.setString(std::to_string(this->layer));
    this->layerText.setFillColor(sf::Color::White);
    this->layerText.setCharacterSize(14);
    this->layerText.setOutlineColor(sf::Color::Black);
    this->layerText.setOutlineThickness(-1.f);
    this->layerText.setPosition(x + 2, y + 2);
}

// Function to set the fill color of a sprite based on an integer value
sf::Color Tile::setGreyColor(int value, int minIntensity) {
    // Map the value to the range [0, 10]
    int greyLevel = mapToRange(value, 0, 10);

    // Convert the grey level to a range between 0 and 255
    int intensity = static_cast<int>((greyLevel / 10.0) * (255 - minIntensity)) + minIntensity;

    // Set the fill color
    return sf::Color(intensity, intensity, intensity);
}


int Tile::mapToRange(int value, int minVal, int maxVal) {
    return std::min(std::max(value, minVal), maxVal);
}