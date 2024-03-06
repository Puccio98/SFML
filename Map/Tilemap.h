#ifndef SFML_TILEMAP_H
#define SFML_TILEMAP_H

#include "../Tile/Tile.h"

class Tilemap {
private:
    unsigned gridSizeU;
    float gridSizeF;
    unsigned layers;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Tile *>>> map;
    sf::Texture tileTextureSheet;
    sf::IntRect textureRect;

public:
    Tilemap(float gridSize, unsigned width, unsigned height);

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target);

    void addTile(unsigned index_x, unsigned index_y, unsigned index_z);

    void removeTile(unsigned index_x, unsigned index_y, unsigned index_z);

    void changeTile();
};


#endif //SFML_TILEMAP_H
