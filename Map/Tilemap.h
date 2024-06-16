#ifndef SFML_TILEMAP_H
#define SFML_TILEMAP_H

#include "../Tile/Tile.h"
#include "../Entities/Entity.h"

class Tilemap {
private:
    unsigned gridSizeU;
    float gridSizeF;
    unsigned maxLayerIndex;
    sf::Vector2u maxSizeGrid;
    sf::Vector2f maxSizeWorld;
    std::vector<std::vector<std::vector<Tile *>>> map;
    std::string texturePath;
    sf::Texture tileTextureSheet;
    sf::Font font;

    void setMaxLayer();

public:
    explicit Tilemap(const std::string &file_name, sf::Font &font);

    virtual ~Tilemap();

    void update();

    const std::vector<std::vector<std::vector<Tile *>>> &getMap() const;

    unsigned int getMaxLayerIndex() const;

    void render(sf::RenderTarget &target, Entity *entity, unsigned layerIndex);

    void render(sf::RenderTarget &target);

    void addTile(const TileData &tileData);

    void addTexture(int index_x, int index_y, const sf::Vector2f &texturePosition);

    void removeTile(unsigned index_x, unsigned index_y);

    const sf::Texture &getTileTextureSheet() const;

    void saveToFile(std::string file_name);

    void loadFromFile(std::string file_name);

    void clear();

    std::tuple<bool, bool>
    checkCollision(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape) const;

    std::tuple<bool, bool> checkOutOfBounds(const sf::RectangleShape &rectangleShape) const;

    std::tuple<bool, bool>
    checkTileCollision(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape,
                       const std::tuple<bool, bool> &collided) const;

    sf::Vector2i getGridPosition(const sf::Vector2f &absolutePosition) const;

    std::tuple<sf::Vector2i, sf::Vector2i>
    getCollisionBounds(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape, int dir) const;

    std::tuple<bool, bool>
    getForbiddenDirections(const sf::RectangleShape &currentShape, const sf::RectangleShape &nextShape,
                           const std::tuple<bool, bool> &collided) const;

    void renderTileLayer(int i, int j, sf::RenderTarget &target);

    void loadTile(const std::string &line);

    std::vector<Tile *> *getTileLayers(int x, int y);
};


#endif //SFML_TILEMAP_H
