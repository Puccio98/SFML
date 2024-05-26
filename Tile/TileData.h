#include <stack>

struct TileData {
    int index_x, index_y, index_z;
    /**
     * Definisce la posizione della texture nello sheet, quindi determina la texture da applicare
     */
    sf::Vector2f texturePosition;
    std::vector<TILE_TYPES> types;
};

