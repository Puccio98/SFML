#ifndef SFML_TILEMAP_H
#define SFML_TILEMAP_H

#include "../Tile/Tile.h"

class Tilemap {
private:
    unsigned gridSizeU;
    float gridSizeF;
    unsigned layers;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Tile>>> map;

public:
    Tilemap();

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target);
};


#endif //SFML_TILEMAP_H
