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
#include"../enums/tile_types.cpp"
#include "TileData.h"

class Tile {
private:
    std::string getTypesAsString() const;

    std::string getSpritesAsString() const;

    void initShapes(sf::Texture &textureSheet,
                    const std::vector<sf::Vector2f> &texturePositions);

    const TileData tiledata;
    sf::Text layerText;

    float get_x();
    float get_y();

protected:
    std::vector<sf::RectangleShape> sprites;
    sf::RectangleShape defaultSprite;

    std::vector<TILE_TYPES> tileTypes;
public:

    Tile(const TileData &tileData, sf::Texture &texture,
         const std::vector<sf::Vector2f> &texturePositions,
         const std::vector<TILE_TYPES> &tileTypes, sf::Font &font);

    virtual ~Tile();

    void update();

    void render(sf::RenderTarget &target);

    std::string getAsString(unsigned x, unsigned y, unsigned z) const;

    bool isOfType(TILE_TYPES type);

    void initLayerText(sf::Font &font);

    sf::Color setGreyColor(int value, int minIntensity);

    int mapToRange(int value, int minVal, int maxVal);

    void addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition);

    void setCollisionOutline(sf::RectangleShape &texture);
};

#endif //SFML_TILE_H
