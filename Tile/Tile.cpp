#include "Tile.h"

#include <utility>

Tile::Tile(TileData tileData, sf::Texture &texture,
           sf::Font &font, bool hud) : tiledata(std::move(tileData)), hud(hud) {
    this->initLayerText(font);
    this->initShapes(texture);
}

Tile::Tile(TileData tileData, sf::Texture &texture,
           sf::Font &font) : Tile(std::move(tileData), texture, font, false) {}

Tile::~Tile() = default;

void Tile::render(sf::RenderTarget &target) {
    if (this->tiledata.sprites.empty()) {
        target.draw(defaultSprite);
    }

    for (const auto &sprite: this->tiledata.sprites) {
        target.draw(sprite);
    }

    if (this->hud) {
        target.draw(this->layerText);
    }
}

void Tile::update(float dt, std::vector<Enemy *> &enemies) {

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
    for (TILE_BEHAVIOURS i: tiledata.behaviours) {
        s.append(std::to_string(static_cast<int>(i)) + " ");
    }

    return s;
}

bool Tile::isOfType(TILE_BEHAVIOURS type) {
    return std::find(this->tiledata.behaviours.begin(), this->tiledata.behaviours.end(), type) !=
           tiledata.behaviours.end();
}

std::string Tile::getSpritesAsString() const {
    std::string s;

    for (const sf::RectangleShape &sprite: this->tiledata.sprites) {
        s.append(
                std::to_string(sprite.getTextureRect().left) + " " + std::to_string(sprite.getTextureRect().top) + " "
        );
    }
    return s;
}

void Tile::initShapes(sf::Texture &textureSheet) {
    if (tiledata.texturePositions.empty()) {
        defaultSprite.setSize(sf::Vector2f(this->tiledata.gridSize, this->tiledata.gridSize));
        defaultSprite.setPosition(get_x(), get_y());
        defaultSprite.setFillColor(this->setGreyColor(this->tiledata.index_z, 30.f));
        if (hud) {
            this->setCollisionOutline(defaultSprite);
        }
    }

    for (sf::Vector2f texturePosition: tiledata.texturePositions) {
        addTexture(textureSheet, texturePosition);
    }
}

void
Tile::addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition) {
    sf::IntRect textureRect = sf::IntRect(texturePosition.x, texturePosition.y, this->tiledata.gridSize,
                                          this->tiledata.gridSize);
    if (!this->tiledata.sprites.empty()) {
        // Controllo che non stia inserendo la stessa texture di prima
        if (this->tiledata.sprites[this->tiledata.sprites.size() - 1].getTextureRect() == textureRect) {
            return;
        }
    }

    sf::RectangleShape texture;
    texture.setSize(sf::Vector2f(this->tiledata.gridSize, this->tiledata.gridSize));
    texture.setPosition(get_x(), get_y());
    texture.setTexture(&textureSheet);
    texture.setTextureRect(textureRect);

    if (hud) {
        this->setCollisionOutline(texture);
    }

    this->tiledata.sprites.push_back(texture);
}

void Tile::setCollisionOutline(sf::RectangleShape &texture) {
    if (isOfType(TILE_BEHAVIOURS::COLLISION)) {
        texture.setOutlineColor(sf::Color(255, 0, 0, 150));
        texture.setOutlineThickness(-2);
    }
}

void Tile::initLayerText(sf::Font &font) {
    this->layerText.setFont(font);
    this->layerText.setString(std::to_string(this->tiledata.index_z));
    this->layerText.setFillColor(sf::Color::White);
    this->layerText.setCharacterSize(12);
    this->layerText.setOutlineColor(sf::Color::Black);
    this->layerText.setOutlineThickness(-1.f);
    this->layerText.setPosition(get_x() + 2, get_y() + 2);
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

float Tile::get_x() {
    return tiledata.index_x * tiledata.gridSize;
}

float Tile::get_y() {
    return tiledata.index_y * tiledata.gridSize;
}

const TileData &Tile::getTiledata() const {
    return tiledata;
}

