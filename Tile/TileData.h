#include <vector>
#include <System/Vector2.hpp>
#include"../enums/tile_types.cpp"

struct TileData {
    int index_x;
    int index_y;
    int index_z;
    float gridSize;
    /**
     * Definisce le posizioni della texture nello sheet, quindi determina la texture da applicare
     */
    std::vector<sf::Vector2f> texturePositions;
    std::vector<TILE_TYPES> types;
};

