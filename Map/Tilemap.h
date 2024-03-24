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

public:
    Tilemap(float gridSize, unsigned width, unsigned height, sf::Texture &_tileTextureSheet);

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target);

    void addTile(unsigned index_x, unsigned index_y, unsigned index_z, sf::Vector2f tileTexturePosition);

    void removeTile(unsigned index_x, unsigned index_y, unsigned index_z);

    const sf::Texture &getTileTextureSheet() const;
};


#endif //SFML_TILEMAP_H
