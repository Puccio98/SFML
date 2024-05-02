#ifndef SFML_TILEMAP_H
#define SFML_TILEMAP_H

#include "../Tile/Tile.h"
#include "../Tile/TileData.h"
#include "../Entities/Entity.h"

class Tilemap {
private:
    unsigned gridSizeU;
    float gridSizeF;
    unsigned layers;
    sf::Vector2u maxSize;
    std::vector<std::vector<std::vector<Tile *>>> map;
    std::string texturePath;
    sf::Texture tileTextureSheet;

public:
    Tilemap(const std::string &file_name);

    virtual ~Tilemap();

    void update();

    void render(sf::RenderTarget &target, Entity* entity = nullptr);

    void addTile(const TileData &tileData);

    void removeTile(unsigned index_x, unsigned index_y, unsigned index_z);

    const sf::Texture &getTileTextureSheet() const;

    void saveToFile(std::string file_name);

    void loadFromFile(std::string file_name);

    void clear();

    void checkCollision(Entity* entity);

};


#endif //SFML_TILEMAP_H
