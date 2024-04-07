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


class Tile {
private:
protected:
    sf::RectangleShape shape;
    TILE_TYPES type;
    bool collision;

public:
    Tile(float x, float y, float gridSizeF, sf::Texture &texture, sf::Vector2f &tileTexturePosition,
         bool collision = false,
         TILE_TYPES type = TILE_TYPES::DEFAULT);

    virtual ~Tile();

    void update();

    void render(sf::RenderTarget &target);

    std::string getAsString() const;
};

#endif //SFML_TILE_H
