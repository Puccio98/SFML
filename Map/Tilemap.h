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

public:
    Tilemap(float gridSize, unsigned width, unsigned height);

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target);

    void addTile();

    void removeTile();
};


#endif //SFML_TILEMAP_H
