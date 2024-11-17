#pragma once

#include "Tile/MapObjectData.h"

class MapObject {
private:
protected:
    MapObjectData *data;
    sf::RectangleShape defaultSprite;
    bool hud = false;

    virtual void initShapes(sf::Texture &textureSheet);

    virtual sf::Color setDefaultColor(int value, int minIntensity);

    int mapToRange(int value, int minVal, int maxVal);

public:
    explicit MapObject(MapObjectData *data, bool hud);

    virtual ~MapObject();

    float get_x();

    float get_y();

    virtual void addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition);

};