#include "MapObject.h"

MapObject::MapObject(MapObjectData *data, bool hud) : data(data), hud(hud) {

}

MapObject::~MapObject() {
    delete data;

}

void MapObject::initShapes(sf::Texture &textureSheet) {
    if (this->data->texturePositions.empty()) {
        this->defaultSprite.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));
        this->defaultSprite.setPosition(get_x(), get_y());
        this->defaultSprite.setFillColor(this->setDefaultColor(this->data->index_z, 30.f));
    } else {
        for (sf::Vector2f texturePosition: this->data->texturePositions) {
            this->addTexture(textureSheet, texturePosition);
        }
    }
}

void MapObject::initLayerText(sf::Font &font) {
    this->layerText.setFont(font);
    this->layerText.setString(this->getLayerTextString());
    this->layerText.setFillColor(sf::Color::White);
    this->layerText.setCharacterSize(12);
    this->layerText.setOutlineColor(sf::Color::Black);
    this->layerText.setOutlineThickness(-1.f);
    this->layerText.setPosition(get_x() + 2, get_y() + 2);
}

float MapObject::get_x() {
    return this->data->index_x * this->data->gridSize;
}

float MapObject::get_y() {
    return this->data->index_y * this->data->gridSize;
}

void
MapObject::addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition) {
    sf::IntRect textureRect = sf::IntRect(texturePosition.x, texturePosition.y, this->data->gridSize,
                                          this->data->gridSize);
    if (!this->data->sprites.empty()) {
        // Controllo che non stia inserendo la stessa texture di prima
        if (this->data->sprites[this->data->sprites.size() - 1].getTextureRect() == textureRect) {
            return;
        }
    }

    sf::RectangleShape texture;
    texture.setSize(sf::Vector2f(this->data->gridSize, this->data->gridSize));
    texture.setPosition(get_x(), get_y());
    texture.setTexture(&textureSheet);
    texture.setTextureRect(textureRect);

    this->data->sprites.push_back(texture);
}

sf::Color MapObject::setDefaultColor(int value, int minIntensity) {
    // Map the value to the range [0, 10]
    int greyLevel = mapToRange(value, 0, 10);

    // Convert the grey level to a range between 0 and 255
    int intensity = static_cast<int>((greyLevel / 10.0) * (255 - minIntensity)) + minIntensity;

    // Set the fill color
    return sf::Color(intensity, intensity, intensity);
}

int MapObject::mapToRange(int value, int minVal, int maxVal) {
    return std::min(std::max(value, minVal), maxVal);
}

MapObjectData *MapObject::getData() const {
    return data;
}

void MapObject::update(float dt, std::vector<Entity *> &entities) {

}

void MapObject::render(sf::RenderTarget &target) {
    if (this->data->sprites.empty()) {
        target.draw(defaultSprite);
    }

    for (const auto &sprite: this->data->sprites) {
        target.draw(sprite);
    }
}

std::string MapObject::getLayerTextString() {
    return std::to_string(this->data->index_z);
}

