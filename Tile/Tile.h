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

class Tile {
private:
protected:
    sf::RectangleShape shape;

public:
    Tile(float x, float y, float gridSizeF);

    virtual ~Tile();

    void update();

    void render(sf::RenderTarget &target);
};


#endif //SFML_TILE_H
