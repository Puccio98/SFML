#include <stack>

struct TileData {
    int index_x, index_y, index_z;
    sf::Vector2f textureRect;
    std::vector<TILE_TYPES> types;
};

