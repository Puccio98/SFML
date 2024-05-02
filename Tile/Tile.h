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
    std::string getTypesAsString() const;

protected:
    sf::RectangleShape shape;
    std::vector<TILE_TYPES> tileTypes;

public:
    Tile(float x, float y, float gridSizeF, sf::Texture &texture, const sf::Vector2f &tileTexturePosition,
         const std::vector<TILE_TYPES> &tileTypes);

    virtual ~Tile();

    void update();

    void render(sf::RenderTarget &target);

    std::string getAsString() const;
};

#endif //SFML_TILE_H
