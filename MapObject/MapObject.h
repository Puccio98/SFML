#pragma once

#include "MapObjectData.h"
#include "../Entities/Entity.h"

class MapObject {
private:
    static int mapToRange(int value, int minVal, int maxVal);

protected:
    MapObjectData *data;
    sf::RectangleShape defaultSprite;
    bool hud = false;
    sf::Text layerText;

    void initLayerText(sf::Font &font);

    virtual void initShapes(sf::Texture &textureSheet);

    virtual sf::Color setDefaultColor(int value, int minIntensity);

    virtual std::string getLayerTextString();

public:
    MapObjectData *getData() const;

public:
    explicit MapObject(MapObjectData *data, bool hud);

    virtual ~MapObject();

    virtual void update(float dt, std::vector<Entity *> &entities);

    virtual void render(sf::RenderTarget &target);

    float get_x();

    float get_y();

    virtual void addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition);

};