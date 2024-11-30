#pragma once

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<sstream>
#include<vector>

#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Graphics.hpp"
#include "TileData.h"
#include "../MapObject.h"

class Tile : public MapObject {
private:
    std::string getTypesAsString() const;

    std::string getSpritesAsString() const;

    void initShapes(sf::Texture &textureSheet) override;

    void setCollisionOutline(sf::RectangleShape &texture);

public:

    Tile(TileData tileData, sf::Texture &texture, sf::Font &font, bool hud);

    Tile(TileData tileData, sf::Texture &texture, sf::Font &font);

    virtual ~Tile();

    const TileData *getTiledata() const;

    void update(float dt, std::vector<Entity *> &entities) override;

    void render(sf::RenderTarget &target) override;

    std::string getAsString(unsigned x, unsigned y, unsigned z) const;

    bool hasBehaviour(TILE_BEHAVIOURS type);

    void addTexture(sf::Texture &textureSheet, const sf::Vector2f &texturePosition) override;

    void initTile(sf::Font &font, sf::Texture &texture);
};