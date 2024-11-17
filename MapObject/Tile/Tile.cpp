#include "Tile.h"

#include <utility>

Tile::Tile(TileData tileData, sf::Texture &texture,
           sf::Font &font, bool hud) : MapObject(new TileData(std::move(tileData)), hud) {
    this->initTile(font, texture);
}

Tile::Tile(TileData tileData, sf::Texture &texture,
           sf::Font &font) : Tile(std::move(tileData), texture, font, false) {}

Tile::~Tile() = default;

void Tile::render(sf::RenderTarget &target) {
    if (this->data->sprites.empty()) {
        target.draw(defaultSprite);
    }

    for (const auto &sprite: this->data->sprites) {
        target.draw(sprite);
    }

    if (this->hud) {
        target.draw(this->layerText);
    }
}

void Tile::update(float dt, std::vector<Entity *> &entities) {

}

std::string Tile::getAsString(unsigned x, unsigned y, unsigned z) const {
    std::stringstream ss;
    ss << "p " << x << " " << y << " " << z
       << " t_p " << this->getSpritesAsString()
       << " t_t " << this->getTypesAsString();
    return ss.str();
}

std::string Tile::getTypesAsString() const {
    auto *tileData = dynamic_cast<TileData *>(data);
    std::string s;
    for (TILE_BEHAVIOURS i: tileData->behaviours) {
        s.append(std::to_string(static_cast<int>(i)) + " ");
    }

    return s;
}

bool Tile::hasBehaviour(TILE_BEHAVIOURS type) {
    auto *tileData = dynamic_cast<TileData *>(data);
    return std::find(tileData->behaviours.begin(), tileData->behaviours.end(), type) !=
           tileData->behaviours.end();
}

std::string Tile::getSpritesAsString() const {
    std::string s;

    for (const sf::RectangleShape &sprite: this->data->sprites) {
        s.append(
                std::to_string(sprite.getTextureRect().left) + " " + std::to_string(sprite.getTextureRect().top) + " "
        );
    }
    return s;
}

void Tile::initShapes(sf::Texture &textureSheet) {
    MapObject::initShapes(textureSheet);

    if (this->data->texturePositions.empty() && hud) {
        this->setCollisionOutline(defaultSprite);
    }
}

void Tile::setCollisionOutline(sf::RectangleShape &texture) {
    if (hasBehaviour(TILE_BEHAVIOURS::COLLISION)) {
        texture.setOutlineColor(sf::Color(255, 0, 0, 150));
        texture.setOutlineThickness(-2);
    }
}

void Tile::initLayerText(sf::Font &font) {
    this->layerText.setFont(font);
    this->layerText.setString(std::to_string(this->data->index_z));
    this->layerText.setFillColor(sf::Color::White);
    this->layerText.setCharacterSize(12);
    this->layerText.setOutlineColor(sf::Color::Black);
    this->layerText.setOutlineThickness(-1.f);
    this->layerText.setPosition(get_x() + 2, get_y() + 2);
}

const TileData *Tile::getTiledata() const {
    return dynamic_cast<TileData *>(this->data);
}

void Tile::addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition) {
    MapObject::addTexture(textureSheet, texturePosition);
    if (hud) {
        if (!this->data->sprites.empty()) {
            this->setCollisionOutline(this->data->sprites.back());
        }
    }
}

void Tile::initTile(sf::Font &font, sf::Texture &texture) {
    this->initLayerText(font);
    this->initShapes(texture);
}

