#ifndef SFML_TILE_H
#define SFML_TILE_H

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<vector>

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include "TileData.h"

class Tile {
private:
    std::string getTypesAsString() const;

    std::string getSpritesAsString() const;

    void initShapes(sf::Texture &textureSheet);

    const TileData tiledata;
    sf::Text layerText;

    float get_x();

    float get_y();

    bool hud = false;

protected:
    std::vector<sf::RectangleShape> sprites;
    sf::RectangleShape defaultSprite;

public:

    Tile(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud);

    Tile(TileData tileData, sf::Texture &texture, sf::Font &font);

    virtual ~Tile();

    void update();

    void render(sf::RenderTarget &target);

    void render(sf::RenderTarget &target, bool hud);

    std::string getAsString(unsigned x, unsigned y, unsigned z) const;

    bool isOfType(TILE_TYPES type);

    void initLayerText(sf::Font &font);

    sf::Color setGreyColor(int value, int minIntensity);

    int mapToRange(int value, int minVal, int maxVal);

    void addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition);

    void setCollisionOutline(sf::RectangleShape &texture);
};

#endif //SFML_TILE_H
