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
    std::string texturePath;
    sf::Texture tileTextureSheet;

    void clear();

public:
    Tilemap(const std::string &file_name);

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target);

    void addTile(unsigned index_x, unsigned index_y, unsigned index_z, sf::Vector2f tileTexturePosition, std::vector<TILE_TYPES>& tileTypes);

    void removeTile(unsigned index_x, unsigned index_y, unsigned index_z);

    const sf::Texture &getTileTextureSheet() const;

    void saveToFile(std::string file_name);

    void loadFromFile(std::string file_name);
};


#endif //SFML_TILEMAP_H
